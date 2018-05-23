//
// Created by 孙庆耀 on 2018/5/22.
//

#include "../src/database.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <check.h>


void test_app_io(const char *test_name,
                 const char *input,
                 const char *expected,
                 void (*launch_app)(void));


START_TEST (test_master_null_test)
    {
        ck_assert_ptr_null(NULL);
    }
END_TEST


START_TEST (test_master_inserts_and_retreives)
    {
        char *input = "insert 1 user1 person1@example.com\n"
                      "select\n"
                      ".exit\n";
        char *expected = "db > Executed.\n"
                         "db > (1, user1, person1@example.com)\n"
                         "Executed.\n"
                         "db > Fare thee well.\n";

        test_app_io("inserts_and_retreives",
                    input, expected, launch_database);
    }
END_TEST


Suite *make_master_suite(void) {
    Suite *s = suite_create("master");
    TCase *tc_core = tcase_create("core");

    suite_add_tcase(s, tc_core);
    tcase_add_test(tc_core, test_master_null_test);
    tcase_add_test(tc_core, test_master_inserts_and_retreives);

    return s;
}


void test_app_io(const char *test_name,
                 const char *input,
                 const char *expected,
                 void (*launch_app)(void)) {
    errno = 0;

    const char *input_fname_fmt = "/tmp/temp.test.%s.input";
    char *input_fname = malloc(strlen(input_fname_fmt) + strlen(test_name) + 1);
    sprintf(input_fname, input_fname_fmt, test_name);
    // write input to file
    FILE *input_fp = fopen(input_fname, "w");
    fputs(input, input_fp);
    fclose(input_fp);
    // redirect input
    freopen(input_fname, "r", stdin);
    free(input_fname);

    const char *output_fname_fmt = "/tmp/temp.test.%s.output.XXXXXX";
    char *output_fname = malloc(strlen(output_fname_fmt) + strlen(test_name) + 1);
    sprintf(output_fname, output_fname_fmt, test_name);
    int output_fd = mkstemp(output_fname);
    // redirect output
    freopen(output_fname, "w", stdout);
    setbuf(stdout, NULL);
    free(output_fname);


    pid_t child_pid = fork();
    if (child_pid == 0) {
        launch_app();
    } else {
        int stat_loc;
        waitpid(child_pid, &stat_loc, WUNTRACED);
    }


    struct stat buf;
    if (fstat(output_fd, &buf) < 0) {
        perror("fstat");
        exit(EXIT_FAILURE);
    }
    size_t output_len = (size_t) buf.st_size;

    char *output = malloc(output_len + 1);
    FILE *output_fp = fdopen(output_fd, "r");
    fread(output, 1, output_len, output_fp);
    output[output_len] = '\0';
    fclose(output_fp);

    if (errno) {
        perror("File IO");
        exit(EXIT_FAILURE);
    }

    char *output_ptr = output, *tofree, *expected_ptr;
    tofree = expected_ptr = strdup(expected);
    char *output_line = NULL, *expected_line = NULL;
    while (output_ptr && expected_ptr) {
        output_line = strsep(&output_ptr, "\n");
        expected_line = strsep(&expected_ptr, "\n");
        ck_assert_str_eq(output_line, expected_line);
    }
    // make sure the end of the string was reached
    ck_assert_ptr_null(output_ptr);
    ck_assert_ptr_null(expected_ptr);

    free(tofree);
    free(output);
}
