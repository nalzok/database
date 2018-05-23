//
// Created by 孙庆耀 on 2018/5/21.
//

#include <check.h>


START_TEST (test_vm_null_test)
    {
        ck_assert_ptr_null(NULL);
    }
END_TEST

Suite *make_vm_suite(void) {
    Suite *s = suite_create("vm");
    TCase *tc_core = tcase_create("core");

    suite_add_tcase(s, tc_core);
    tcase_add_test(tc_core, test_vm_null_test);

    return s;
}
