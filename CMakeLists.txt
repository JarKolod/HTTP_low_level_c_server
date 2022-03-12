cmake_minimum_required(VERSION 3.10)
project(httpServer)


add_subdirectory(src)

add_executable(server src/server.c)

target_link_libraries(server
		PRIVATE
			${PROJECT_NAME}_lib)
