cmake_minimum_required(VERSION 2.6)
PROJECT(CMake)
set(CMAKE_C_COMPILER g++)
add_compile_options(-std=c++11)
set(SRC_LIST main.cpp)
ADD_EXECUTABLE(main ${SRC_LIST})
TARGET_LINK_LIBRARIES(main muduo_net)
TARGET_LINK_LIBRARIES(main muduo_base)
TARGET_LINK_LIBRARIES(main pthread)
