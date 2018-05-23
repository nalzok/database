//
// Created by 孙庆耀 on 2018/5/22.
//

#include "check_database.h"


int main(void) {
    SRunner *sr = srunner_create(make_master_suite());
    srunner_add_suite(sr, make_repl_suite());
    srunner_add_suite(sr, make_compiler_suite());
    srunner_add_suite(sr, make_vm_suite());

    srunner_run_all(sr, CK_NORMAL);
    int number_failed = srunner_ntests_failed(sr);

    srunner_free(sr);

    return number_failed;
}