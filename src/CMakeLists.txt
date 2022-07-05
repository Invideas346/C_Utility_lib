cmake_minimum_required(VERSION 3.16.3)

if(LIBARY)
    set(SOURCE_FILES
            linked_lists.c
            string_struct.c
            vector.c
            key_map.c
            manchester.c
            crc.c
    )
    add_library(${PROJECT_NAME} ${SOURCE_FILES})
endif(LIBARY)

if(EXE)
    set(SOURCE_FILES
            main.c
            linked_lists.c
            string_struct.c
            vector.c
            key_map.c
            manchester.c
            crc.c
    )
    add_executable(${PROJECT_NAME} ${SOURCE_FILES})
endif(EXE)