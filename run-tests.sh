#!/bin/bash

make clean
make all
./mutex-test && \
    ./mutex-thread-test && \
    echo 'ok'
