//
// Created by 孙庆耀 on 2018/5/19.
//

#ifndef DATABASE_REPL_H
#define DATABASE_REPL_H

#include <sys/types.h>

typedef struct InputBuffer_t {
    char *buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

InputBuffer *new_input_buffer(void);

void print_prompt(void);

void read_input(InputBuffer *);

#endif //DATABASE_REPL_H
