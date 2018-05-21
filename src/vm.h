//
// Created by 孙庆耀 on 2018/5/20.
//

#ifndef DATABASE_VM_H
#define DATABASE_VM_H

#include "compiler.h"


// Representation of a serialized row (without structure padding)
#define size_of_attribute(Struct, Attribute) (sizeof(((Struct){0}).Attribute))

#define ID_SIZE             size_of_attribute(Row, id)
#define USERNAME_SIZE       size_of_attribute(Row, username)
#define EMAIL_SIZE          size_of_attribute(Row, email)
#define ID_OFFSET           0
#define USERNAME_OFFSET     (ID_OFFSET + ID_SIZE)
#define EMAIL_OFFSET        (USERNAME_OFFSET + USERNAME_SIZE)
#define ROW_SIZE            (ID_SIZE + USERNAME_SIZE + EMAIL_SIZE)

#define TABLE_MAX_PAGES     100
#define PAGE_SIZE           4096
#define ROWS_PER_PAGE       (PAGE_SIZE / ROW_SIZE)
#define TABLE_MAX_ROWS      (TABLE_MAX_PAGES * ROWS_PER_PAGE)

typedef struct Table_t {
    void *pages[TABLE_MAX_PAGES];
    size_t num_rows;
} Table;

Table *new_table(void);

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
