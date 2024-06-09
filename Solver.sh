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
  ./Hybrid.o < $1 > "solution.sol"
  visualizer $1 "solution.sol"
  pace2024verify -c $1 "solution.sol"
  rm "solution.sol"
elif [ $option_v -eq 1 ]; then
  ./Hybrid.o < $1 > "solution.sol"
  visualizer $1 "solution.sol" 
  rm "solution.sol"
elif [ $option_c -eq 1 ]; then
  ./Hybrid.o -c < $1
  pace2024verify -c $1 "solution.sol"
else
  ./Hybrid.o < $1
fi

rm Hybrid.o