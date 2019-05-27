LINK_DIRECTORIES (
    ./lib
)

add_executable(
    bomberman
    ./src/test.cpp
)
set(CMAKE_CXX_FLAGS "-L./lib/  -L/usr/X11R6/lib64 -lGL -lXxf86vm -lXext -lX11 -lXcursor")
set(CMAKE_EXE_LINKER_FLAGS "-L./lib/  -L/usr/X11R6/lib64 -lGL -lXxf86vm -lXext -lX11 -lXcursor")
set_target_properties(bomberman PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

target_link_libraries(
    bomberman
    module_tmp
    Irrlicht
)
