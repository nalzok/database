# Main executable

set(MAIN_SOURCES
        main.c)

set(LIB_SOURCES
        database.c
        repl.c
        compiler.c
        vm.c)

set(HEADERS
        database.h
        repl.h
        compiler.h
        vm.h)

add_library(libdatabase STATIC ${LIB_SOURCES} ${HEADERS})

add_executable(main ${MAIN_SOURCES} ${HEADERS})
target_link_libraries(main libdatabase)
