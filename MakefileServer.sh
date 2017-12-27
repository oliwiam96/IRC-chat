#!/bin/bash
g++ -Wall -pthread -l sqlite3 database.cpp server.cpp -o server
