
# Local servers
./bench_ycsb --logtostderr=1 --id=0 --servers="" --protocol="Silo" --partition_num=24 --threads=12 --batch_size=10000 --read_write_ratio=80 --cross_ratio=5 --keys=40000 --zipf=0.0 --two_partitions=True


# Experiments
servers="127.0.0.1:8000;127.0.0.1:8001"
./bench_ycsb --logtostderr=1 --id=0 --servers="$servers" --protocol="Scar" --partition_num=24 --threads=12 --batch_size=10000 --read_write_ratio=80 --cross_ratio=5 --keys=40000 --zipf=0.0 --two_partitions=True --replica_group=3

./bench_ycsb --logtostderr=1 --id=1 --servers="$servers" --protocol="Scar" --partition_num=24 --threads=12 --batch_size=10000 --read_write_ratio=80 --cross_ratio=5 --keys=40000 --zipf=0.0 --two_partitions=True --replica_group=3

# How about the replication and replay?