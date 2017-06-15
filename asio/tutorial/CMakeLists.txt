add_compile_options(-std=c++11)

add_executable(timer2 timer2.cpp)
add_executable(timer3 timer3.cpp)
add_executable(timer4 timer4.cpp)
add_executable(timer5 timer5.cpp)
add_executable(timer6 timer6.cpp)

target_link_libraries(timer2 muduo_net muduo_base pthread)
target_link_libraries(timer3 muduo_net muduo_base pthread)
target_link_libraries(timer4 muduo_net muduo_base pthread)
target_link_libraries(timer5 muduo_net muduo_base pthread)
target_link_libraries(timer6 muduo_net muduo_base pthread)
