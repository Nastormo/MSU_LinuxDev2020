cmake_minimum_required(VERSION 3.8)

INCLUDE(CheckIncludeFiles)

project(Window)

set(TRASH "CMakeFiles cmake_install.cmake CMakeCache.txt window")

add_custom_target(allclean rm -rf ${TRASH}
    DEPENDS ${TRASH}
    VERBATIM
)

find_library(NCURSESW_LIBRARY ncursesw)
if (NOT NCURSESW_LIBRARY)
    message(FATAL_ERROR "ncursesw not found")
endif ()

find_library(PCRE2_LIBRARY pcre2-8)
if (NOT PCRE2_LIBRARY)
    message(FATAL_ERROR "pcre2-8 not found")
endif ()

CHECK_INCLUDE_FILES("ncurses.h" NCURSES_H)
if (NOT NCURSES_H)
    message(FATAL_ERROR "ncurses.h not found")
endif ()

CHECK_INCLUDE_FILES("pcre2.h" PCRE2_H)
if (NOT PCRE2_H)
    message(STATUS "pcre2.h not found")
endif ()

set(SOURCE_EXE Window.c)

option(WITHOUT_UTF "PCRE2 UTF support" OFF)

if(WITHOUT_UTF)
    message(STATUS "Disable UTF")
    add_definitions(-DUSE_UTF=0)
else()
    message(STATUS "Enable UTF")
    add_definitions(-DUSE_UTF=1)
endif()

add_executable(window ${SOURCE_EXE})

target_link_libraries(window ${NCURSESW_LIBRARY} ${PCRE2_LIBRARY})