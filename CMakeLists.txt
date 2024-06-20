cmake_minimum_required(VERSION 3.28)
project(ejemplo02_mpi)

set(CMAKE_CXX_STANDARD 17)

find_package(MPI REQUIRED)
message(STATUS "Run ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${MPIEXEC_MAX_NUMPROCS}")

include_directories(${MPI_INCLUDE_PATH})

add_executable(ejemplo02_mpi main.cpp)
target_link_libraries(ejemplo02_mpi MPI::MPI_CXX)