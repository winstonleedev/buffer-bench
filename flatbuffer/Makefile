CXXFLAGS = -I/home/thanhphu/Code/flatbuffers/include `pkg-config --cflags grpc grpc++`
LDFLAGS = -lgrpc -lgrpc++ -lgrpc++_unsecure -lgrpc++_reflection -lgpr

# LD_LIBRARY_PATH ?= /home/thanhphu/Code/grpc/libs/dbg
.PHONY: all
all: fbbench_generated.h fbbench_server fbbench_client

fbbench_generated.h: fbbench.fbs
	flatc --grpc --cpp $<

fbbench_server: server.cpp fbbench.grpc.fb.cc fbbench_generated.h fbbench.grpc.fb.h
	g++ -std=c++17 -g $(CXXFLAGS) server.cpp fbbench.grpc.fb.cc $(LDFLAGS) -o ../cmake-build-debug/$@

fbbench_client: client.cpp fbbench.grpc.fb.cc fbbench_generated.h fbbench.grpc.fb.h
	g++ -std=c++17 -g $(CXXFLAGS) client.cpp fbbench.grpc.fb.cc $(LDFLAGS) -o ../cmake-build-debug/$@

clean:
	rm fbbench_server
	rm fbbench_client