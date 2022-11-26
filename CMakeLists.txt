cmake_minimum_required(VERSION 3.16.3)
project(CUtility)

include_directories(include)

set(EXE ON)
set(LOG ON)
#add_definitions(-DNO_LOG)

add_subdirectory(src)