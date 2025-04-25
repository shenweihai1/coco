servers="127.0.0.1:5000;127.0.0.1:5001"

./bench_ycsb --logtostderr=1 --id=0 --servers="$servers"  \
     --protocol="Silo" --partition_num=48 --threads=24 \
     --batch_size=10000 --read_write_ratio=50 --cross_ratio=5 \
     --keys=1000000 --zipf=0.0 --two_partitions=True --replica_group=3 > ~/coco/logs/nshards2-id0.log 2>&1 &
