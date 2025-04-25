
def generate_commands(nshards):
    w = open("./cmds-{n}.sh".format(n=nshards), "w") 

    servers = []
    for e in open("./ips.pub","r").readlines():
        servers.append(e.strip())
    
    base_port = 5000
    for i in range(len(servers)):
        servers[i] = servers[i]+":"+str(base_port+i)
    
    txt = ""
    for i in range(nshards):
        subw = open("./cmds-{n}-{i}.sh".format(n=nshards, i=i), "w") 
        subw_txt = ""
        subw_txt += 'servers="{servers}"\n'.format(servers=";".join(servers[:nshards]))
        subw_txt += """
./bench_ycsb --logtostderr=1 --id={id} --servers="$servers"  \\
     --protocol="Silo" --partition_num={partition_num} --threads=24 \\
     --batch_size=10000 --read_write_ratio=50 --cross_ratio=5 \\
     --keys=1000000 --zipf=0.0 --two_partitions=True --replica_group=3 > ~/coco/logs/nshards{nshards}-id{id}.log 2>&1 &
""".format(id=i, partition_num=24*nshards, nshards=nshards)
        subw.write(subw_txt)


    for i in range(nshards):
        txt += 'ssh {host} "ulimit -n 20000;cd coco;bash {subcmd}" &\n'.format(host=servers[i].split(":")[0], subcmd="./scripts/cmds-{n}-{i}.sh".format(n=nshards, i=i))

    w.write(txt)


if __name__ == "__main__":
    for nshards in range(1,11):
        generate_commands(nshards)