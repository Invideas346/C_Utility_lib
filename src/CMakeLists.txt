cmake_minimum_required(VERSION 3.16.3)

if(LOG)
    set(LOG_SOURCES log.c)
else()
    set(LOG_SOURCES)
endif(THREADS)

set(SOURCE_FILES
        main.c
        linked_lists.c
        string_struct.c
        vector.c
        key_map.c
        manchester.c
        crc.c
        ${LOG_SOURCES}
        thread.c
)

if(EXE)
    add_executable(${PROJECT_NAME} ${SOURCE_FILES})
endif(EXE)
if(LIBARY)
    add_library(${PROJECT_NAME} ${SOURCE_FILES})
endif(LIBARY)