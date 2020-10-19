cmake_minimum_required(VERSION 3.8)

project(Window)

find_library(NCURSESW_LIBRARY ncursesw)
find_library(PCRE2_LIBRARY pcre2-8)

set(SOURCE_EXE Window.c)

option(WITHOUT_UTF "PCRE2 UTF support" OFF)

message(STATUS ${WITHOUT_UTF})

if(WITHOUT_UTF)
    message(STATUS "Disable UTF")
    add_definitions(-DUSE_UTF=0)
else()
    message(STATUS "Enable UTF")
    add_definitions(-DUSE_UTF=1)
endif()
unset(WITHOUT_UTF)

add_executable(window ${SOURCE_EXE})

target_link_libraries(window ${NCURSESW_LIBRARY} ${PCRE2_LIBRARY})