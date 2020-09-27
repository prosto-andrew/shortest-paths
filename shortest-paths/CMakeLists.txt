cmake_minimum_required(VERSION 3.5)
project(shortest-paths)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
#set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS "${CMAKE_CXX_FLAGS} -o2 -s")

add_executable(shortest-paths main.cpp dijkstra/dijkstra.cpp dijkstra/dijkstra.hpp dijkstra/vertex.cpp dijkstra/vertex.hpp dijkstra/edge.cpp dijkstra/edge.hpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(shortest-paths Threads::Threads)

file(GLOB shortest-paths-DATA ${CMAKE_SOURCE_DIR}/data/*)
add_custom_command(TARGET shortest-paths POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:shortest-paths>/data)

file(GLOB shortest-paths-DIJKSTRA ${CMAKE_SOURCE_DIR}/dijkstra/*)
add_custom_command(TARGET shortest-paths POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/dijkstra $<TARGET_FILE_DIR:shortest-paths>/dijkstra)
