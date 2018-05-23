//
// Created by 孙庆耀 on 2018/5/21.
//

#include "../src/repl.h"

#include <check.h>


START_TEST (test_repl_new_input_buffer)
    {
        ck_assert_ptr_nonnull(new_input_buffer());
    }
END_TEST

Suite *make_repl_suite(void) {
    Suite *s = suite_create("repl");
    TCase *tc_core = tcase_create("core");

    suite_add_tcase(s, tc_core);
    tcase_add_test(tc_core, test_repl_new_input_buffer);

    return s;
}
