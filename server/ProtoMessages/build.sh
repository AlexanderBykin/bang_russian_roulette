#!/bin/bash

#rm -d -R ../../brr_client/brr/ProtoMessages/*
rm -d -R ../../brr_client_cpp/Classes/ProtoMessages/*
rm -d -R ../core/src/main/java/ProtoMessages/*

for f in *.proto
do
# ../../mingchen-protobuf-ios/compiler/src/protoc --objc_out=../../brr_client/brr/ProtoMessages/ "$f";
# ../../mingchen-protobuf-ios/compiler/src/protoc --java_out=../core/src/main/java/ "$f";
/usr/local/lib/platform/i386-sim/bin/protoc --java_out=../core/src/main/java/ "$f";
/usr/local/lib/platform/i386-sim/bin/protoc --cpp_out=../../brr_client_cpp/Classes/ProtoMessages/ "$f";
done