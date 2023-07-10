#include "unit.h"

int main() {
    int fail = 0;

    Suite* s21_calc_tests[] = {suite_s21_calc_bad_input(),
                               suite_s21_calc_correct_input(),
                               suite_s21_calc_test(), NULL};

    for (int i = 0; s21_calc_tests[i] != NULL; i++) {
        SRunner* sr = srunner_create(s21_calc_tests[i]);

        srunner_set_fork_status(sr, CK_NOFORK);
        srunner_run_all(sr, CK_NORMAL);

        fail += srunner_ntests_failed(sr);
        srunner_free(sr);
    }

    printf("========= FAILED: %d =========\n", fail);

    return fail == 0 ? 0 : 1;

    return 0;
}