cmake_minimum_required(VERSION 2.6)
PROJECT(ECHO)
set(CMAKE_C_COMPILER g++)
add_compile_options(-std=c++11)
set(SRC_LIST echo.o main.cpp)
ADD_EXECUTABLE(echo ${SRC_LIST})
TARGET_LINK_LIBRARIES(echo muduo_net)
TARGET_LINK_LIBRARIES(echo muduo_base)
TARGET_LINK_LIBRARIES(echo pthread)
