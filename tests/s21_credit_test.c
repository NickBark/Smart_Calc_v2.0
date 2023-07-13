#include "unit.h"

START_TEST(credit_1) {
  Credit cr;
  cr.term = 36;
  cr.totalCredit = 1200000;
  cr.type = 0;
  cr.interestRate = 12;

  creditCalcCore(&cr);

  ck_assert_double_eq_tol(cr.monthlyPayment, 39857.17, 1e-0);
  ck_assert_double_eq_tol(cr.overpaymentOnCredit, 234858.12, 1e-0);
  ck_assert_double_eq_tol(cr.totalPayment, 1434858.12, 1e-0);
}
END_TEST

START_TEST(credit_2) {
  Credit cr;
  cr.term = 9;
  cr.totalCredit = 1200000;
  cr.type = 1;
  cr.interestRate = 12;
  cr.date = 0;
  cr.mainMonthSum = cr.totalCredit / cr.term;
  cr.totalPayment = 0.;
  cr.overpaymentOnCredit = 0.;
  cr.monthlyPayment = 0.;

  cr.days = 1;
  int dateTmp = 7;
  int currYear = 2023;
  double monthlyPayments[255] = {145563.47, 144204.56, 142538.81,
                                 141486.75, 139908.67, 138768.47,
                                 137398.90, 135868.85, 134688.55};

  for (int i = 0; i < cr.term; i++) {
    cr.date = (dateTmp + i) % 12;
    if (!((currYear + (dateTmp - 1 + i) / 12) % 4)) {
      cr.leapYear = 1;
    } else {
      cr.leapYear = 0;
    }
    if (!((currYear + (dateTmp + i) / 12) % 4)) {
      cr.nextLeapYear = 1;
    } else {
      cr.nextLeapYear = 0;
    }
    creditCalcCore(&cr);

    ck_assert_double_eq_tol(cr.monthlyPayment, monthlyPayments[i], 1e-0);
  }

  ck_assert_double_eq_tol(cr.totalPayment, 1260427.52, 1e-0);
  ck_assert_double_eq_tol(cr.overpaymentOnCredit, 60427.52, 1e-0);
}
END_TEST

START_TEST(credit_3) {
  Credit cr;
  cr.term = 9;
  cr.totalCredit = 1200000;
  cr.type = 1;
  cr.interestRate = 12;
  cr.date = 0;
  cr.mainMonthSum = cr.totalCredit / cr.term;
  cr.totalPayment = 0.;
  cr.overpaymentOnCredit = 0.;
  cr.monthlyPayment = 0.;

  cr.days = 24;
  int dateTmp = 7;
  int currYear = 2024;
  double monthlyPayments[255] = {145530.05, 144174.86, 142513.66,
                                 141464.48, 139890.71, 138765.59,
                                 137410.04, 135788.12, 134692.26};

  for (int i = 0; i < cr.term; i++) {
    cr.date = (dateTmp + i) % 12;
    if (!((currYear + (dateTmp - 1 + i) / 12) % 4)) {
      cr.leapYear = 1;
    } else {
      cr.leapYear = 0;
    }
    if (!((currYear + (dateTmp + i) / 12) % 4)) {
      cr.nextLeapYear = 1;
    } else {
      cr.nextLeapYear = 0;
    }
    creditCalcCore(&cr);

    ck_assert_double_eq_tol(cr.monthlyPayment, monthlyPayments[i], 1e-0);
  }

  ck_assert_double_eq_tol(cr.totalPayment, 1260230., 1e-0);
  ck_assert_double_eq_tol(cr.overpaymentOnCredit, 60230., 1e-0);
}
END_TEST

Suite *suite_s21_calc_credit(void) {
  Suite *s = suite_create("\033[45mcredit\033[0m");
  TCase *tc_credit = tcase_create("credit");
  suite_add_tcase(s, tc_credit);

  tcase_add_test(tc_credit, credit_1);
  tcase_add_test(tc_credit, credit_2);
  tcase_add_test(tc_credit, credit_3);

  return s;
}