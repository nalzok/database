//
// Created by 孙庆耀 on 2018/5/19.
//

#include "repl.h"

#include <stdlib.h>
#include <stdio.h>


InputBuffer *new_input_buffer(void) {
    InputBuffer *input_buffer = calloc(1, sizeof *input_buffer);
    if (input_buffer == NULL) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }

    return input_buffer;
}

void print_prompt(void) { printf("db > "); }

void read_input(InputBuffer *input_buffer) {
    ssize_t bytes_read = getline(&input_buffer->buffer,
                                 &input_buffer->buffer_length,
                                 stdin);

    if (bytes_read <= 0) {
        printf("Error reading input");
        exit(EXIT_FAILURE);
    }

    input_buffer->input_length = bytes_read;

    // Discard trailing newline. if any
    if (input_buffer->buffer[bytes_read - 1] == '\n') {
        input_buffer->buffer[bytes_read - 1] = '\0';
        input_buffer->input_length--;
    }
}