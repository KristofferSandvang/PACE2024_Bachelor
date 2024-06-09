#!/usr/bin/env bash
usage() {
  echo "Usage: $0 [-s] [-c] <filename>"
  exit 1
}

# Initialize variables
option_v=0
option_c=0

# Parse command line options
while getopts ":vc" opt; do
  case ${opt} in
    v )
      option_v=1
      ;;
    c )
      option_c=1
      ;;
    \? )
      usage
      ;;
  esac
done

shift $((OPTIND -1))

if [ -z "$1" ]; then
  usage
  exit 1
fi

g++ -std=c++17 -Ofast ./src/Hybrid.cpp ./src/Graph.cpp ./src/Vertex.cpp ./src/CrossingMinimizers/Crossingminimizer.cpp ./src/CrossingMinimizers/Barycenter.cpp ./src/CrossingMinimizers/Median.cpp ./src/CrossingMinimizers/OptimizedBC.cpp ./src/CrossingMinimizers/OptimizedMedian.cpp ./src/CrossingMinimizers/BarycenterMed.cpp ./src/CrossingMinimizers/MedianBary.cpp -o Hybrid.o

if [ $? -ne 0 ]; then
  echo "Compilation failed"
  exit 1
fi

if [ $option_v -eq 1 ] && [ $option_c -eq 1 ]; then
  ./Hybrid.o < $filename > solution.sol
  visualizer $filename solution.sol
  pace2024verify -c $filename solution.sol
  rm solution.sol
elif [ $option_v -eq 1 ]; then
  ./Hybrid.o < $filename > solution.sol
  visualizer $filename solution.sol 
  rm solution.sol
elif [ $option_c -eq 1 ]; then
  ./Hybrid.o -c < $filename
  pace2024verify -c $filename solution.sol
else
  ./Hybrid.o < $filename
fi

rm Hybrid.o