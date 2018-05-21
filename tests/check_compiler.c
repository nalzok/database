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
        ck_assert_int_eq(do_meta_command(input_buffer), META_COMMAND_UNRECOGNIZED_COMMAND);
    }
END_TEST

Suite *repl_suite(void) {
    Suite *s = suite_create("REPL");
    TCase *tc_core = tcase_create("Core");

    suite_add_tcase(s, tc_core);
    tcase_add_test(tc_core, test_do_meta_command);

    return s;
}

int main(void) {
    Suite *s = repl_suite();
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    int number_failed = srunner_ntests_failed(sr);

    srunner_free(sr);

    return number_failed;
}