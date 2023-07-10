#include "unit.h"

START_TEST(bad_input_1) {
    Priority pr = {};
    initPriority(&pr);
    char const inputStr[][255] = {"qwrqwrwq", "sin(x))", "cossin(x)", "Sin()",
                                  "1sinx",    "2sin(3)", "sin1",      "sin",
                                  "cos",      "tan"};
    char resultStr[255] = {};
    for (size_t i = 0; i < SIZE_ARR(inputStr); i++) {
        ck_assert_int_eq(1, shuntingYard(inputStr[i], resultStr, &pr));
    }
    free(pr.priority);
}
END_TEST

Suite *suite_s21_calc_bad_input(void) {
    Suite *s = suite_create("\033[45mbad_input\033[0m");
    TCase *tc_bad_input = tcase_create("bad_input");
    suite_add_tcase(s, tc_bad_input);

    tcase_add_test(tc_bad_input, bad_input_1);

    return s;
}
