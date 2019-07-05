#!/bin/zsh

nohup ./flatbuffer/fbbench_server &
server1PID=$!
nohup ./cmake-build-debug/buffer-bench-pb-server &
server2PID=$!
nohup ./cmake-build-debug/buffer-bench-raw-server &
server3PID=$!

echo > result.txt
for i in {1..10}
do
    ./flatbuffer/fbbench_client >> result.txt
    ./cmake-build-debug/buffer-bench-pb-client >> result.txt
    ./cmake-build-debug/buffer-bench-raw-client >> result.txt
done

kill $server1PID $server2PID $server3PID