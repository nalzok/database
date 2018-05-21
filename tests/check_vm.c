//
// Created by 孙庆耀 on 2018/5/21.
//

#include <check.h>


START_TEST (test_repl_new_input_buffer)
    {
        ck_assert_ptr_null(NULL);
    }
END_TEST

Suite *repl_suite(void) {
    Suite *s = suite_create("REPL");
    TCase *tc_core = tcase_create("Core");

    suite_add_tcase(s, tc_core);
    tcase_add_test(tc_core, test_repl_new_input_buffer);

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