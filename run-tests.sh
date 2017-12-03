#!/bin/bash

make clean
make all
./test && \
    ./test && \
    echo 'ok'
