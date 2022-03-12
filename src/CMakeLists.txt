project(httpServer)

add_subdirectory(connection_handling)
add_subdirectory(io_helper)

add_library(${PROJECT_NAME}_lib
		STATIC
			io_helper_lib
			connectionHandling_lib)
