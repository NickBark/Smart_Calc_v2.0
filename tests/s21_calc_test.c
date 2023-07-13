#include "unit.h"
#define NUM1 5

START_TEST(calc_test_1) {
  Priority pr = {};
  initPriority(&pr);

  char const inputStr[NUM1][255] = {"sin(23.23)", "cos(54.34)",
                                    "asin(1) + cos(142.412)", "tan(32.23)",
                                    "1/0"};
  double answers[NUM1] = {-0.94541032274, -0.59548677907, 1.064861201,
                          1.0590603639};
  double result = 0.;
  char resultStr[255] = {};

  for (int i = 0; i < NUM1 - 1; i++) {
    initPriority(&pr);
    shuntingYard(inputStr[i], resultStr, &pr);
    calcus(resultStr, &pr, 1, &result);
    ck_assert_double_eq_tol(result, answers[i], 1e-7);
  }

  initPriority(&pr);
  if (!shuntingYard(inputStr[4], resultStr, &pr))
    calcus(resultStr, &pr, 1, &result);

  ck_assert_double_nan(result);
}
END_TEST

Suite *suite_s21_calc_test(void) {
  Suite *s = suite_create("\033[45mcalc_test\033[0m");
  TCase *tc_calc_test = tcase_create("calc_test");
  suite_add_tcase(s, tc_calc_test);

  tcase_add_test(tc_calc_test, calc_test_1);

  return s;
}