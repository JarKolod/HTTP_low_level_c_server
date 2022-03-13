cmake_minimum_required(VERSION 3.10)
project(httpServer)


add_executable(server src/server.c src/connection_handling/connectionHandling.c src/io_helper/io_helper.c)

