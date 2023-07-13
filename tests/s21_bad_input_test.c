#include "unit.h"

START_TEST(bad_input_1) {
  Priority pr = {};
  initPriority(&pr);
  char const inputStr[][255] = {
      "qwrqwrwq",     "sin(x))", "cossin(x)", "Sin()", "1sinx",    "2sin(3)",
      "sin1",         "sin",     "cos",       "tan",   "1.1.+2.1", "1.1.1+2.3",
      "cos(3)sin(3)", "3x",      "x3",        "X3",    "3X",       "-9 * -9"};
  char resultStr[255] = {};
  for (size_t i = 0; i < SIZE_ARR(inputStr); i++) {
    ck_assert_int_eq(1, shuntingYard(inputStr[i], resultStr, &pr));
  }
}
END_TEST

START_TEST(bad_input_2) {
  Priority pr = {};
  double answer = 0.;

  char const inputStr[][255] = {"tan(3.1415926535/2)", "log(-1)", "ln(-100)",
                                "asin(5)", "acos(-3)"};
  char resultStr[255] = {};
  for (size_t i = 0; i < SIZE_ARR(inputStr); i++) {
    initPriority(&pr);
    shuntingYard(inputStr[i], resultStr, &pr);
    ck_assert_int_eq(1, calcus(resultStr, &pr, 1, &answer));
  }
}
END_TEST

Suite *suite_s21_calc_bad_input(void) {
  Suite *s = suite_create("\033[45mbad_input\033[0m");
  TCase *tc_bad_input = tcase_create("bad_input");
  suite_add_tcase(s, tc_bad_input);

  tcase_add_test(tc_bad_input, bad_input_1);
  tcase_add_test(tc_bad_input, bad_input_2);

  return s;
}
