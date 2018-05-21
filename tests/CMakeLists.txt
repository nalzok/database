# Unit tests

enable_testing()

# REPL
add_executable(check_repl check_repl.c ${HEADERS})
target_link_libraries(check_repl database ${CHECK_LIBRARIES})
add_test(NAME check_repl COMMAND check_repl)

# Compiler
add_executable(check_compiler check_compiler.c ${HEADERS})
target_link_libraries(check_compiler database ${CHECK_LIBRARIES})
add_test(NAME check_compiler COMMAND check_compiler)

# Virtual machine
add_executable(check_vm check_vm.c ${HEADERS})
target_link_libraries(check_vm database ${CHECK_LIBRARIES})
add_test(NAME check_vm COMMAND check_vm)
