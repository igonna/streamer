cmake_minimum_required(VERSION 3.8)

project(streamer)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SOURCES
	src/streamer/streamer.cpp
	src/logger/logger.cpp
)

add_executable(${PROJECT_NAME} app/main.cpp ${SOURCES})