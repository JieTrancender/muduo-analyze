AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS=daytime time
daytime_SOURCES=src/daytime.h src/daytime.cpp src/daytime_main.cpp
time_SOURCES=src/time.h src/time.cpp src/time_main.cpp
daytime_LDADD=-lmuduo_net -lmuduo_base -lpthread
time_LDADD=-lmuduo_net -lmuduo_base -lpthread

CXXFLAGS=-std=c++11

