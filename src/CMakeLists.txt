cmake_minimum_required(VERSION 3.16.3)

set(SOURCE_FILES
    main.c
    linkedLists.c
    stringStruct.c
    dynamicArray.c
)

if(LIBARY)
    add_library(${PROJECT_NAME} ${SOURCE_FILES})
endif(LIBARY)

if(EXE)
    add_executable(${PROJECT_NAME} ${SOURCE_FILES})
endif(EXE)