servers="127.0.0.1:5000;127.0.0.1:5001;127.0.0.1:5002;127.0.0.1:5003"

./bench_ycsb --logtostderr=1 --id=1 --servers="$servers"  \
     --protocol="Silo" --partition_num=96 --threads=24 \
     --batch_size=10000 --read_write_ratio=50 --cross_ratio=5 \
     --keys=1000000 --zipf=0.0 --two_partitions=True --replica_group=3 > ~/coco/logs/nshards4-id1.log 2>&1 &
