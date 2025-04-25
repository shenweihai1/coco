servers="127.0.0.1:5000;127.0.0.1:5001;127.0.0.1:5002;127.0.0.1:5003;127.0.0.1:5004"

./bench_ycsb --logtostderr=1 --id=3 --servers="$servers"  \
     --protocol="Silo" --partition_num=120 --threads=24 \
     --batch_size=10000 --read_write_ratio=50 --cross_ratio=5 \
     --keys=1000000 --zipf=0.0 --two_partitions=True --replica_group=3 > ~/coco/logs/nshards5-id3.log 2>&1 &
