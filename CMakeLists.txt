cmake_minimum_required(VERSION 3.10)
project(httpServer)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_executable(server 
src/server.c 
	src/connection_handling/connectionHandling.c 
	src/io_helper/io_helper.c
	src/connection_handling/requestParsing.c
)

target_link_libraries(server Threads::Threads)
