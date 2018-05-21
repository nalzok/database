//
// Created by 孙庆耀 on 2018/5/20.
//

#include "compiler.h"
#include "vm.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>


Table *new_table(void) {
    Table *table = calloc(1, sizeof *table);
    if (!table) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }

    return table;
}

ExecuteResult execute_insert(Statement *statement, Table *table) {
    if (table->num_rows >= TABLE_MAX_ROWS) {
        return EXECUTE_TABLE_FULL;
    }

    Row *row_to_insert = &statement->row_to_insert;
    serialize_row(row_slot(table, table->num_rows), row_to_insert);
    table->num_rows++;

    return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(Statement *statement, Table *table) {
    (void) statement;
    Row row;
    for (size_t i = 0; i < table->num_rows; i++) {
        deserialize_row(&row, row_slot(table, i));
        print_row(&row);
    }
    return EXECUTE_SUCCESS;
}

ExecuteResult execute_statement(Statement *statement, Table *table) {
    switch (statement->type) {
        case STATEMENT_INSERT:
            return execute_insert(statement, table);
        case STATEMENT_SELECT:
            return execute_select(statement, table);
    }
}

void serialize_row(void *dst, Row *src) {
    memcpy(dst + ID_OFFSET, &src->id, ID_SIZE);
    memcpy(dst + USERNAME_OFFSET, &src->username, USERNAME_SIZE);
    memcpy(dst + EMAIL_OFFSET, &src->email, EMAIL_SIZE);
}

void deserialize_row(Row *dst, void *src) {
    memcpy(&dst->id, src + ID_OFFSET, ID_SIZE);
    memcpy(&dst->username, src + USERNAME_OFFSET, USERNAME_SIZE);
    memcpy(&dst->email, src + EMAIL_OFFSET, EMAIL_SIZE);
}

void *row_slot(Table *table, size_t row_num) {
    size_t page_num = row_num / ROWS_PER_PAGE;
    void *page = table->pages[page_num];
    if (!page) {
        page = table->pages[page_num] = calloc(1, PAGE_SIZE);
    }
    if (!page) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }

    size_t row_offset = row_num % ROWS_PER_PAGE;
    size_t byte_offset = row_offset * ROW_SIZE;

    return page + byte_offset;
}

void print_row(Row *row) {
    printf("(%"PRIuMAX", %s, %s)\n", row->id, row->username, row->email);
}