#!/bin/bash

mkdir -p dev

cd dev

cmake   -DCMAKE_PREFIX_PATH=$MY_GRPC_DIR \
        -DCMAKE_BUILD_TYPE=Debug \
        -DBUILD_DEV=y \
        ..

make -j 4