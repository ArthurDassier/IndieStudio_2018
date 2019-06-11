project(utils)

include_directories(./include)

if (WIN32)
    include_directories(
        "C:/Boost/include/boost-1_70"
    )
endif ()

add_library(utils
    STATIC
    ./srcs/Packet.cpp
)

target_include_directories(utils INTERFACE ./include)
SET_TARGET_PROPERTIES(utils PROPERTIES LINKER_LANGUAGE CXX)

# add_subdirectory(tests)
