//
// Created by 孙庆耀 on 2018/5/21.
//

#include "../src/repl.h"
#include "../src/compiler.h"

#include <check.h>


START_TEST (test_do_meta_command)
    {
        InputBuffer *input_buffer = new_input_buffer();
        input_buffer->buffer = ".hello";
        ck_assert_int_eq(do_meta_command(input_buffer),
                         META_COMMAND_UNRECOGNIZED_COMMAND);
    }
END_TEST

Suite *make_compiler_suite(void) {
    Suite *s = suite_create("compiler");
    TCase *tc_core = tcase_create("core");

    suite_add_tcase(s, tc_core);
    tcase_add_test(tc_core, test_do_meta_command);

    return s;
}
