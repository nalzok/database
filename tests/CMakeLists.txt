# Unit tests

enable_testing()

set(MAIN_SOURCES
        check_database.c)

set(LIB_SOURCES
        master_suite.c
        repl_suite.c
        compiler_suite.c
        vm_suite.c)

set(HEADERS
        check_database.h)

add_executable(check_database ${MAIN_SOURCES} ${LIB_SOURCES} ${HEADERS})
target_link_libraries(check_database libdatabase ${CHECK_LIBRARIES})
add_test(NAME check_database COMMAND check_database)
