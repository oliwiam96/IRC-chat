#!/bin/bash
g++ -Wall -pthread  database.cpp server.cpp -o server -lsqlite3
