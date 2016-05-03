#!/bin/bash

dx=2

BIN=./magic

for distance in `seq 5 5 40`
do
    $BIN $distance $dx > logs/data_${distance}.log
    echo finished $distance
done
