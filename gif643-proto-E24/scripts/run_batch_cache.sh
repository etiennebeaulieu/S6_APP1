#!/usr/bin/env bash
# Assumes this is run in the build/ folder.

mkdir -p output
time ./asset_conv 8 ../scripts/testCache.txt
