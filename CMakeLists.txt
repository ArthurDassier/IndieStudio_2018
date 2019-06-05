cmake_minimum_required(VERSION 3.9.1)
project(bomberman)

#add_subdirectory(Additional)
add_subdirectory(module_tmp)
add_subdirectory(Bomberman)
add_subdirectory(client)
add_subdirectory(server)

#
# file(
#     GLOB_RECURSE
#     main_src
#         src/*
# )
#
# add_executable(
#     bomberman
#     ${main_src}
# )
