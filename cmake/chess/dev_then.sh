#!/bin/bash

mkdir -p dev_then

cd dev_then

cmake   -DCMAKE_PREFIX_PATH=$MY_GRPC_DIR \
        -DCMAKE_BUILD_TYPE=Debug \
        -DBUILD_DEV_THEN=y \
        ..

make -j 4