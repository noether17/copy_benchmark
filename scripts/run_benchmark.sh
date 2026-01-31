#!/bin/bash

path_to_copy_benchmark=$1
eval $path_to_copy_benchmark \
  --benchmark_out=benchmark_data_$(date +'%Y%m%d%H%M%S').json
