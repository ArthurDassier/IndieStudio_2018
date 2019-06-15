project(bot)

if (WIN32)
    include_directories(./include)
    set(CMAKE_CXX_FLAGS "-D_WIN32_WINNT=0x0601 /EHsc")
else ()
    include_directories(./include)
endif ()

add_library(bot
    STATIC
    ./src/Bot.cpp
)

if (WIN32)
    target_include_directories(bot INTERFACE ./include)
else ()
    target_include_directories(bot INTERFACE ./include)
endif ()

target_link_libraries(
    bot
    game
)

SET_TARGET_PROPERTIES(bot PROPERTIES LINKER_LANGUAGE CXX)

# add_subdirectory(tests)
