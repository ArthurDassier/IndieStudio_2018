cmake_minimum_required(VERSION 2.6)
project(bomberman)

file(
    GLOB_RECURSE
    main_src
        src/*
)

add_executable(
    bomberman
    ${main_src}
)
