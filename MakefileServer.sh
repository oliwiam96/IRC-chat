#!/bin/bash
g++ -Wall -pthread -std=c++11 database.cpp server.cpp -o server -lsqlite3 &
