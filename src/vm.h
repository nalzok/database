//
// Created by 孙庆耀 on 2018/5/20.
//

#ifndef DATABASE_VM_H
#define DATABASE_VM_H

#include "compiler.h"
#include "table.h"

typedef enum ExecuteResult_t {
    EXECUTE_SUCCESS,
    EXECUTE_TABLE_FULL,
} ExecuteResult;

ExecuteResult execute_insert(Statement *statement, Table *table);

ExecuteResult execute_select(Statement *statement, Table *table);

ExecuteResult execute_statement(Statement *statement, Table *table);

void serialize_row(void *dst, Row *src);

void deserialize_row(Row *dst, void *src);

void *row_slot(Table *table, size_t row_num);

void print_row(Row *row);

#endif //DATABASE_VM_H
