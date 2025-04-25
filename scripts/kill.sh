ROOT=$HOME
ps aux|grep -i bench|awk '{print $2}'|xargs kill -9; 
ps aux|grep -i bench_ycsb|awk '{print $2}'|xargs kill -9; 
ps aux|grep -i bench_tpcc|awk '{print $2}'|xargs kill -9; 
