#!/bin/bash

make clean
make all
./test && \
    ./thread-test && \
    echo 'ok'
