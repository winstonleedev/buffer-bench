# buffer-bench
A benchmark of Flatbuffer / Protobuf / Raw struct for C++, designed to run on Linux

Updated Jun-2019 for use with latest versions of flatbuffer and protobuf

## How to run
* Install ~~[flatbuffers](https://github.com/google/flatbuffers)~~ Must use a [custom version](https://github.com/thanhphu/flatbuffers). This version has code generation modified to avoid duplicate declarations with newer versions of GRPC.
* Install ~~[grpc](https://github.com/grpc/grpc)~~ Must use a [custom version](https://github.com/thanhphu/grpc). This version expose some private fields that flatbuffers need
* ~~Install [protobuf](https://github.com/protocolbuffers/protobuf)~~ Will be installed together with grpc above
* Install [evpp](https://github.com/Qihoo360/evpp)
* Install zlib `sudo apt-get install zlibc`
* Open in CLion
* Sync CMake project
* Press build
* Run make in `/flatbuffer`
* Run `runAll.sh`
* Result will be written to `result.txt`

## Sample result

```
=================================
FLATBUF bench start...
total bytes = 15898507595776707224
* 0.003065 create time
* 0.238328 receive time
* 0.002950 use
* 0.000782 free
* 0.245125 total time
=================================
PROTOBUF bench start...
total bytes = 0
* 0.000766 create time
* 0.244944 receive time
* 0.001007 use
* 0.000785 free
* 0.247503 total time
=================================
RAW bench start...
total bytes = 54377074000
* 0.001709 create time
* 0.002417 receive time
* 0.000813 use
* 0.000759 free
* 0.005699 total time
```