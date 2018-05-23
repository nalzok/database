//
// Created by 孙庆耀 on 2018/5/23.
//

#ifndef DATABASE_TABLE_H
#define DATABASE_TABLE_H

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

void free_table(Table *table);

#endif //DATABASE_TABLE_H
