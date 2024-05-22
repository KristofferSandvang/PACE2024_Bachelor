cmake_minimum_required(VERSION 3.10)
project(PACE2024)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(PACE2024
    hybrid.cpp
    Graph.cpp
    Vertex.cpp
    CrossingMinimizers/Crossingminimizer.cpp
    CrossingMinimizers/Barycenter.cpp
    CrossingMinimizers/Median.cpp
    CrossingMinimizers/OptimizedBC.cpp
    CrossingMinimizers/OptimizedMedian.cpp
    CrossingMinimizers/ParentMinimizer.cpp
    CrossingMinimizers/OptimizedBCRight.cpp
    CrossingMinimizers/BarycenterMed.cpp
    CrossingMinimizers/MedianBary.cpp
    CrossingMinimizers/BarycenterRev.cpp
    CrossingMinimizers/MedianRev.cpp
)