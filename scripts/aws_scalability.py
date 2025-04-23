#!/usr/local/bin/python3

'''
This script is used to generate commands to plot Figure 14 -- Scalability of Kiva on YCSB benchmark
'''

import sys

from utility import load_ips
from utility import get_cmd_string

# repeat experiments for the following times
REPEAT = 1

num_machines = int(sys.argv[1])
machine_id = int(sys.argv[2]) 
port = int(sys.argv[3]) 

ips = load_ips('ips.txt.'+str(num_machines))

n_machines = len(ips)

threads = 12
batch_size = 10000


# id and servers
# What's difference between id and servers 
def print_ycsb():
    
  read_write_ratio = 80
  zipf = 0.0
  keys = 40000
  cross_ratios = [5]
  n_nodes = [num_machines]

  for n_node in n_nodes:
    if machine_id >= n_node:
      break
    partition_num = threads * n_node
    for cross_ratio in cross_ratios:
      for i in range(REPEAT):
        cmd = get_cmd_string(machine_id, ips[:n_node], port + i)
        print(f'./bench_ycsb --logtostderr=1 --id={machine_id} --servers="{cmd}" --protocol="Silo" --partition_num={partition_num} --threads={threads} --batch_size={batch_size} --read_write_ratio={read_write_ratio} --cross_ratio={cross_ratio} --keys={keys} --zipf={zipf} --two_partitions=True')

def main():
  # ycsb
  print_ycsb()

if __name__ == '__main__':
  main()