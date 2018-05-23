//
// Created by 孙庆耀 on 2018/5/22.
//

#ifndef DATABASE_RUN_SUITES_H
#define DATABASE_RUN_SUITES_H

#include <check.h>

Suite *make_master_suite(void);

Suite *make_repl_suite(void);

Suite *make_compiler_suite(void);

Suite *make_vm_suite(void);

#endif //DATABASE_RUN_SUITES_H
