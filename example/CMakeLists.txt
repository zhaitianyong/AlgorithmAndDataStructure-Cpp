cmake_minimum_required(VERSION 3.16)
project(AlgorithmAndDataStructure_Cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_BUILD_TYPE "Debug")


include_directories(../src)

add_executable(test_sort test_sort.cpp
        ../src/sorts.h
        ../src/maxheap.h
        ../src/testhelper.h
        ../src/testhelper.cpp
)

#add_executable(AlgorithmAndDataStructure_Cpp
#        src/graphs.h
#        src/linkqueue.h
#        src/linkstack.h
#        src/main.cpp
#        src/maxheap.h
#        src/search.h
#        src/singlelink.h
#        src/sorts.cpp
#        src/sorts.h
#        src/testhelper.cpp
#        src/testhelper.h
#        src/trees.h
#        src/weightgraph.h)