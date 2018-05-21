# Main executable

set(MAIN_SOURCES
        main.c)

set(LIB_SOURCES
        repl.c
        compiler.c
        vm.c)

set(HEADERS
        repl.h
        compiler.h
        vm.h)

add_library(database STATIC ${LIB_SOURCES} ${HEADERS})

add_executable(main ${MAIN_SOURCES} ${HEADERS})
target_link_libraries(main database)
