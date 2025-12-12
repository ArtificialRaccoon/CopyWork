cmake_minimum_required(VERSION 3.10)

project(copywork)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "src/*.cpp")

include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(copywork ${sources})

if (WIN32)
    find_package(pdcurses CONFIG QUIET)
    target_include_directories(copywork PRIVATE ${PDCurses_INCLUDE_DIRS})
    target_link_libraries(copywork PRIVATE ${PDCurses_LIBRARIES})
else()
    find_package(Curses REQUIRED)
    target_include_directories(copywork PRIVATE ${CURSES_INCLUDE_DIRS})
    target_link_libraries(copywork PRIVATE ${CURSES_LIBRARIES})
endif()