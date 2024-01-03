#!/bin/bash

mkdir -p build_proto

cd build_proto

cmake   -DCMAKE_PREFIX_PATH=$MY_GRPC_DIR \
        -DPROTO_ONLY=y \
        ..

make -j 4