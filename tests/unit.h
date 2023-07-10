#ifndef SRC_TESTS_UNIT_H
#define SRC_TESTS_UNIT_H

#include <check.h>
#include <string.h>

#include "../s21_calc_core.h"

Suite *suite_s21_calc_bad_input();
Suite *suite_s21_calc_correct_input();
Suite *suite_s21_calc_test();

#endif  //  SRC_TESTS_UNIT_H