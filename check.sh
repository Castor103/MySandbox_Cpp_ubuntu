#!/bin/bash

rm rf ./*

cmake ..&& cmake ..

make clean

time(make -j`nproc`)
