cmake_minimum_required(VERSION 3.15)

project(mastermind_hydra)

set(CMAKE_CXX_COMPILER "mpiCC")
set(GCC_MPI_FLAGS "-lmpi")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${G++_MPI_FLAGS}")

find_package(MPI REQUIRED)

add_executable(mastermind_hydra src/main.cpp src/Guess.cpp src/Challenger.cpp src/Gamemaster.cpp src/Evaluation.cpp src/Utils.cpp src/Range.cpp)