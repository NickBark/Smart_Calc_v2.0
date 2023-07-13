#include "unit.h"

START_TEST(correct_input_1) {
  Priority pr = {};
  initPriority(&pr);
  char const inputStr[][255] = {
      "sin(x)", "cos(x)", "asin(x) + cos(x)", "tan(32,23)", "3 mod 2", "3+x",
      "x+3",    "3 + x",  "x + 3 ",           "-9*-9"};
  char resultStr[255] = {};
  for (size_t i = 0; i < SIZE_ARR(inputStr); i++) {
    ck_assert_int_eq(0, shuntingYard(inputStr[i], resultStr, &pr));
  }
  // free(pr.priority);
}
END_TEST

START_TEST(correct_input_2) {
  char str[255] = {"1.5*((-2))+3.5"};
  char result[255] = {};
  double answer = 0.;
  Priority pr = {};
  initPriority(&pr);
  ck_assert_int_eq(shuntingYard(str, result, &pr), 0);
  calcus(result, &pr, 1, &answer);
  ck_assert_double_eq_tol(answer, 0.5, 1e-7);
  // free(pr.priority);
}
END_TEST

START_TEST(correct_input_3) {
  char str[255] = {"2^2^3"};
  char result[255] = {};
  double answer = 0.;
  Priority pr = {};
  initPriority(&pr);
  ck_assert_int_eq(shuntingYard(str, result, &pr), 0);
  calcus(result, &pr, 1, &answer);
  ck_assert_double_eq_tol(answer, 256, 1e-7);
  // free(pr.priority);
}
END_TEST

START_TEST(correct_input_4) {
  char str[255] = {"(2^2)^3"};
  char result[255] = {};
  double answer = 0.;
  Priority pr = {};
  initPriority(&pr);
  ck_assert_int_eq(shuntingYard(str, result, &pr), 0);
  calcus(result, &pr, 1, &answer);
  ck_assert_double_eq_tol(answer, 64, 1e-7);
  // free(pr.priority);
}
END_TEST

START_TEST(correct_input_5) {
  char str[255] = {"asin(0.523)"};
  char result[255] = {};
  double answer = 0.;
  Priority pr = {};
  initPriority(&pr);
  ck_assert_int_eq(shuntingYard(str, result, &pr), 0);
  calcus(result, &pr, 1, &answer);
  ck_assert_double_eq_tol(answer, 0.550366917610664, 1e-7);
  // free(pr.priority);
}
END_TEST

START_TEST(correct_input_6) {
  char str[255] = {"atan(0.523)"};
  char result[255] = {};
  double answer = 0.;
  Priority pr = {};
  initPriority(&pr);
  ck_assert_int_eq(shuntingYard(str, result, &pr), 0);
  calcus(result, &pr, 1, &answer);
  ck_assert_double_eq_tol(answer, 0.481877852, 1e-7);
}
END_TEST

START_TEST(correct_input_7) {
  char str[255] = {"(sqrt(5.5)+ln(5))^(log(3))"};
  char result[255] = {};
  double answer = 0.;
  Priority pr = {};
  initPriority(&pr);
  ck_assert_int_eq(shuntingYard(str, result, &pr), 0);
  calcus(result, &pr, 1, &answer);
  ck_assert_double_eq_tol(answer, 1.927048845, 1e-7);
}
END_TEST

START_TEST(correct_input_8) {
  char str[255] = {"(sqrt(5.5)+ln(5))^(log(3)+acos(0.145))"};
  char result[255] = {};
  double answer = 0.;
  Priority pr = {};
  initPriority(&pr);
  ck_assert_int_eq(shuntingYard(str, result, &pr), 0);
  calcus(result, &pr, 1, &answer);
  ck_assert_double_eq_tol(answer, 13.67540606, 1e-7);
}
END_TEST

Suite *suite_s21_calc_correct_input(void) {
  Suite *s = suite_create("\033[45mcorrect_input\033[0m");
  TCase *tc_correct_input = tcase_create("correct_input");
  suite_add_tcase(s, tc_correct_input);

  tcase_add_test(tc_correct_input, correct_input_1);
  tcase_add_test(tc_correct_input, correct_input_2);
  tcase_add_test(tc_correct_input, correct_input_3);
  tcase_add_test(tc_correct_input, correct_input_4);
  tcase_add_test(tc_correct_input, correct_input_5);
  tcase_add_test(tc_correct_input, correct_input_6);
  tcase_add_test(tc_correct_input, correct_input_7);
  tcase_add_test(tc_correct_input, correct_input_8);

  return s;
}