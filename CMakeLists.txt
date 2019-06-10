cmake_minimum_required(VERSION 3.9.2)
project(bomberman)

set(CMAKE_CXX_FLAGS -Wno-error)

add_subdirectory(Additional)
add_subdirectory(Bomberman)
add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(game)
