#include "repl.h"
#include "compiler.h"
#include "vm.h"

#include <stdbool.h>
#include <stdio.h>


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
int main(int argc, char **argv) {
    InputBuffer *input_buffer = new_input_buffer();
    Table *table = new_table();
    while (true) {
        print_prompt();
        read_input(input_buffer);

        if (input_buffer->buffer[0] == '.') {
            switch (do_meta_command(input_buffer)) {
                case META_COMMAND_SUCCESS:
                    continue;
                case META_COMMAND_UNRECOGNIZED_COMMAND:
                    printf("Unrecognized command '%s'\n", input_buffer->buffer);
                    continue;
            }
        }

        Statement statement;
        switch (prepare_statement(input_buffer, &statement)) {
            case PREPARE_SUCCESS:
                switch (execute_statement(&statement, table)) {
                    case EXECUTE_SUCCESS:
                        puts("Executed");
                        continue;
                    case EXECUTE_TABLE_FULL:
                        puts("Error: Table full");
                        continue;
                }
            case PREPARE_SYNTAX_ERROR:
                puts("Syntax error. Could not parse statement.");
                continue;
            case PREPARE_UNRECOGNIZED_STATEMENT:
                printf("Unrecognized keyword at start of '%s'\n",
                       input_buffer->buffer);
                continue;
        }
    }
}
#pragma clang diagnostic pop
