//
// Created by 孙庆耀 on 2018/5/20.
//

#ifndef DATABASE_COMPILER_H
#define DATABASE_COMPILER_H

#include "repl.h"

#include <stdint.h>

typedef enum MetaCommandResult_t {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND,
} MetaCommandResult;

typedef enum PrepareResult_t {
    PREPARE_SUCCESS,
    PREPARE_SYNTAX_ERROR,
    PREPARE_UNRECOGNIZED_STATEMENT,
} PrepareResult;

typedef enum StatementType_t {
    STATEMENT_INSERT,
    STATEMENT_SELECT,
} StatementType;

#define COLUMN_USERNAME_SIZE    32
#define COLUMN_EMAIL_SIZE       32

typedef struct Row_t {
    uintmax_t id;
    char username[COLUMN_USERNAME_SIZE];
    char email[COLUMN_EMAIL_SIZE];
} Row;

typedef struct Statement_t {
    StatementType type;
    union {
        Row row_to_insert;
    };
} Statement;

MetaCommandResult do_meta_command(InputBuffer *input_buffer);

PrepareResult prepare_statement(InputBuffer *input_buffer,
                                Statement *statement);

#endif //DATABASE_COMPILER_H
