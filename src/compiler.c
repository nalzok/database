//
// Created by 孙庆耀 on 2018/5/20.
//

#include "compiler.h"

#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include <errno.h>


MetaCommandResult do_meta_command(InputBuffer *input_buffer) {
    if (strcmp(input_buffer->buffer, ".exit") == 0) {
        puts("Fare thee well.");
        exit(EXIT_SUCCESS);
    } else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

PrepareResult prepare_statement(InputBuffer *input_buffer,
                                Statement *statement) {
    if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;

        char *input_id_str = malloc(strlen(input_buffer->buffer));

        int args_assigned = sscanf(input_buffer->buffer,
                                   "insert %[0-9] %s %s",
                                   input_id_str,
                                   statement->row_to_insert.username,
                                   statement->row_to_insert.email);

        if (args_assigned < 3) {
            return PREPARE_SYNTAX_ERROR;
        }

        statement->row_to_insert.id = strtoumax(input_id_str, NULL, 10);

        errno = 0;
        if (errno) {
            perror("strtoumax");
            return PREPARE_SYNTAX_ERROR;
        }

    } else if (strncmp(input_buffer->buffer, "select", 6) == 0) {
        statement->type = STATEMENT_SELECT;
    } else {
        return PREPARE_UNRECOGNIZED_STATEMENT;
    }

    return PREPARE_SUCCESS;
}