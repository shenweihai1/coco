ROOT=$HOME
# ps aux|grep -i D2PC|awk '{print $2}'|xargs sudo kill -9; sleep 1;
ps aux|grep -i D2PC|awk '{print $2}'|xargs kill -9; 
ps aux|grep -i clients|awk '{print $2}'|xargs kill -9; 
skill server; skill timeserver; skill benchClient; skill coorserver; # rm $ROOT/D2PC/*.bin;rm $ROOT/D2PC/logs/*.log; #rm /home/azureuser/D2PC/store/tools/keys
