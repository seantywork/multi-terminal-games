#!/bin/bash

if [ -z "$1" ]
then
    echo "path is empty"
    exit 1
fi


$TARGET_GEN="chess/dev_then"

if [ ! -d "./$TARGET_GEN/" ]
then
    echo "./$TARGET_GEN/ dir doesn't exist"
    exit 1
fi

rm -r ./$TARGET_GEN/*.pem

rm -r ./$TARGET_GEN/*.key

rm -r ./$TARGET_GEN/*.pub

rm -r ./$TARGET_GEN/*.csr

echo "root generating...."

openssl genrsa -out ./$TARGET_GEN/ca_priv.pem 4096

openssl rsa -in ./$TARGET_GEN/ca_priv.pem -outform PEM -pubout -out ./$TARGET_GEN/ca_pub.pem

openssl req -x509 -new -key ./$TARGET_GEN/ca_priv.pem -days 3650 -out ./$TARGET_GEN/ca.pem -subj "/CN=root"

echo "server key pair, csr generating...."

openssl genrsa -out ./$TARGET_GEN/server.key 4096

openssl rsa -in ./$TARGET_GEN/server.key -outform PEM -pubout -out ./$TARGET_GEN/server.pub

openssl req -key ./$TARGET_GEN/server.key -new -sha256 -out ./$TARGET_GEN/server.csr  -subj "/CN=localhost" 

echo "signing requests for server...."

openssl x509 -req -extfile <(printf "subjectAltName = DNS:localhost") -days 365 -in ./$TARGET_GEN/server.csr -CA ./$TARGET_GEN/ca.pem -CAkey ./$TARGET_GEN/ca_priv.pem -CAcreateserial -sha256 -out ./$TARGET_GEN/server.pem 


echo "done!"