cmake_minimum_required(VERSION 3.16.3)

if(LIBARY)
    set(SOURCE_FILES
        linkedLists.c
        stringStruct.c
        dynamicArray.c
        keyMap.c
        manchester.c
    )
    add_library(${PROJECT_NAME} ${SOURCE_FILES})
endif(LIBARY)

if(EXE)
    set(SOURCE_FILES
        main.c
        linkedLists.c
        stringStruct.c
        dynamicArray.c
        keyMap.c
        manchester.c
    )
    add_executable(${PROJECT_NAME} ${SOURCE_FILES})
endif(EXE)