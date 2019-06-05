project(client)

add_library(client STATIC
    ./src/client.cpp
    ./src/core.cpp
    ./src/entity.cpp
    ./src/Irrlicht.cpp
    ./src/clock.cpp
    )

target_include_directories(client INTERFACE ./include)

set(CMAKE_CXX_FLAGS "-L./lib/  -L/usr/X11R6/lib64 -lGL -lXxf86vm -lXext -lX11 -lXcursor -lboost_timer -lpthread -lboost_system")
set(CMAKE_EXE_LINKER_FLAGS "-L./lib/  -L/usr/X11R6/lib64 -lGL -lXxf86vm -lXext -lX11 -lXcursor -lboost_timer -lpthread -lboost_system")

SET_TARGET_PROPERTIES(client PROPERTIES LINKER_LANGUAGE CXX)

# target_include_directories(module_tmp STATIC ./include)
# target_link_libraries(module_tmp STATIC)

add_subdirectory(tests)
