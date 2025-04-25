[![Build Status](https://travis-ci.org/luyi0619/coco.svg?branch=master)](https://travis-ci.org/luyi0619/coco)

# Dependencies

```sh
sudo apt-get update
sudo apt-get install -y zip make cmake g++ libjemalloc-dev libboost-dev libgoogle-glog-dev
```

# Download

```sh
git clone https://github.com/luyi0619/coco.git
```

# Build

```
./compile.sh
```

# Deployment on ubuntu22.04
```
sudo apt-get update
sudo apt-get install -y zip make cmake g++ libjemalloc-dev libboost-dev libgoogle-glog-dev
./compile.sh

# test
./testTPCCDatabase
./testYCSBDatabase
./testSiloRWKey
```

# 2 questions left
1. Where is the code for group-commit replication and replay on the backup? `group_commit` and `replication_request_handler` seem not do actual batch-replication over the socket? do they?
2. How to configuration 3-way replication? parameter `replica_group` does not look right.