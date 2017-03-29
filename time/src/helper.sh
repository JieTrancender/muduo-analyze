#!/bin/bash
g++ -o daytime daytime.h daytime.cpp daytime_main.cpp -lmuduo_net -lmuduo_base -lpthread -std=c++11
