#!/bin/bash

mkdir -p build_proto_then

cd build_proto_then

cmake   -DCMAKE_PREFIX_PATH=$MY_GRPC_DIR \
        -DPROTO_ONLY_THEN=y \
        ..

make -j 4