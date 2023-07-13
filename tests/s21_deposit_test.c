#include "unit.h"

START_TEST(deposit_1) {
  Deposit dp;
  dp.depositAmount = 3500000.;
  dp.periodOfPlacement = 3.;
  dp.interestRate = 8.;
  dp.taxRate = 13.;
  dp.paymentsType = EVERY_MONTH;
  dp.interestCapitalization = 1;
  dp.currentDay = 10;
  dp.currentMoth = 7;
  dp.currentYear = 2023;
  dp.addCount = 0;
  dp.remCount = 0;

  initialDp(&dp);

  depositCalcCore(&dp);

  ck_assert_double_eq_tol(dp.sumInterest, 71050.72, 1e-2);
  ck_assert_double_eq_tol(dp.sumEndTerm, 3571050.72, 1e-2);
  ck_assert_double_eq_tol(dp.sumTax, 0.0, 1e-2);
}
END_TEST

START_TEST(deposit_2) {
  Deposit dp;
  dp.depositAmount = 3500000.;
  dp.periodOfPlacement = 3.;
  dp.interestRate = 8.;
  dp.taxRate = 13.;
  dp.paymentsType = EVERY_MONTH;
  dp.interestCapitalization = 0;
  dp.currentDay = 10;
  dp.currentMoth = 7;
  dp.currentYear = 2023;
  dp.addCount = 0;
  dp.remCount = 0;

  initialDp(&dp);

  depositCalcCore(&dp);

  ck_assert_double_eq_tol(dp.sumInterest, 70575.34, 1e-2);
  ck_assert_double_eq_tol(dp.sumEndTerm, 3500000.00, 1e-2);
  ck_assert_double_eq_tol(dp.sumTax, 0.0, 1e-2);
}
END_TEST

START_TEST(deposit_3) {
  Deposit dp;
  dp.depositAmount = 3500000.;
  dp.periodOfPlacement = 9.;
  dp.interestRate = 8.;
  dp.taxRate = 13.;
  dp.paymentsType = EVERY_MONTH;
  dp.interestCapitalization = 0;
  dp.currentDay = 10;
  dp.currentMoth = 7;
  dp.currentYear = 2023;
  dp.addCount = 0;
  dp.remCount = 0;

  initialDp(&dp);

  depositCalcCore(&dp);

  ck_assert_double_eq_tol(dp.sumInterest, 210747.21, 1e-2);
  ck_assert_double_eq_tol(dp.sumEndTerm, 3500000.00, 1e-2);
  ck_assert_double_eq_tol(dp.sumTax, 7897.14, 1e-2);
}
END_TEST

START_TEST(deposit_4) {
  Deposit dp;
  dp.depositAmount = 3500000.;
  dp.periodOfPlacement = 35.;
  dp.interestRate = 8.;
  dp.taxRate = 13.;
  dp.paymentsType = EVERY_MONTH;
  dp.interestCapitalization = 1;
  dp.currentDay = 10;
  dp.currentMoth = 7;
  dp.currentYear = 2023;
  dp.addCount = 0;
  dp.remCount = 0;

  initialDp(&dp);

  depositCalcCore(&dp);

  ck_assert_double_eq_tol(dp.sumInterest, 916785.40, 1e-2);
  ck_assert_double_eq_tol(dp.sumEndTerm, 4416785.40, 1e-2);
  ck_assert_double_eq_tol(dp.sumTax, 80182.10, 1e-2);
}
END_TEST

START_TEST(deposit_5) {
  Deposit dp;
  dp.depositAmount = 3500000.;
  dp.periodOfPlacement = 35.;
  dp.interestRate = 8.;
  dp.taxRate = 13.;
  dp.paymentsType = EVERY_HALF_YEAR;
  dp.interestCapitalization = 1;
  dp.currentDay = 5;
  dp.currentMoth = 7;
  dp.currentYear = 2023;
  dp.addCount = 1;
  dp.replenishmentList[0].term = EVERY_MONTH;
  dp.replenishmentList[0].money = 10999.;
  dp.remCount = 0;

  initialDp(&dp);

  depositCalcCore(&dp);

  ck_assert_double_eq_tol(dp.sumInterest, 946844.81, 1e-2);
  ck_assert_double_eq_tol(dp.sumEndTerm, 4831809.81, 1e-2);
  ck_assert_double_eq_tol(dp.sumTax, 93839.83, 1e-2);
}
END_TEST

START_TEST(deposit_6) {
  Deposit dp;
  dp.depositAmount = 3500000.;
  dp.periodOfPlacement = 9.;
  dp.interestRate = 8.;
  dp.taxRate = 13.;
  dp.paymentsType = EVERY_YEAR;
  dp.interestCapitalization = 1;
  dp.currentDay = 5;
  dp.currentMoth = 7;
  dp.currentYear = 2025;
  dp.addCount = 1;
  dp.replenishmentList[0].term = EVERY_HALF_YEAR;
  dp.replenishmentList[0].money = 10999.;
  dp.remCount = 0;

  initialDp(&dp);

  depositCalcCore(&dp);

  ck_assert_double_eq_tol(dp.sumInterest, 210408.75, 1e-2);
  ck_assert_double_eq_tol(dp.sumEndTerm, 3721407.75, 1e-2);
  ck_assert_double_eq_tol(dp.sumTax, 17603.14, 1e-2);
}
END_TEST

START_TEST(deposit_7) {
  Deposit dp;
  dp.depositAmount = 3500000.;
  dp.periodOfPlacement = 13.;
  dp.interestRate = 8.;
  dp.taxRate = 13.;
  dp.paymentsType = EVERY_YEAR;
  dp.interestCapitalization = 1;
  dp.currentDay = 5;
  dp.currentMoth = 7;
  dp.currentYear = 2025;
  dp.addCount = 1;
  dp.replenishmentList[0].term = EVERY_HALF_YEAR;
  dp.replenishmentList[0].money = 10999.;
  dp.remCount = 1;
  dp.listPartialWithdrawals[0].term = EVERY_YEAR;
  dp.listPartialWithdrawals[0].money = 888.;

  initialDp(&dp);

  depositCalcCore(&dp);

  ck_assert_double_eq_tol(dp.sumInterest, 306266.02, 1e-2);
  ck_assert_double_eq_tol(dp.sumEndTerm, 3827376.02, 1e-2);
  ck_assert_double_eq_tol(dp.sumTax, 30064.58, 1e-2);
}
END_TEST

START_TEST(deposit_8) {
  Deposit dp;
  dp.depositAmount = 3500000.;
  dp.periodOfPlacement = 24.;
  dp.interestRate = 8.;
  dp.taxRate = 13.;
  dp.paymentsType = EVERY_MONTH;
  dp.interestCapitalization = 1;
  dp.currentDay = 12;
  dp.currentMoth = 7;
  dp.currentYear = 2024;
  dp.addCount = 1;
  dp.replenishmentList[0].term = EVERY_YEAR;
  dp.replenishmentList[0].money = 10999.;
  dp.remCount = 1;
  dp.listPartialWithdrawals[0].term = EVERY_HALF_YEAR;
  dp.listPartialWithdrawals[0].money = 888.;

  initialDp(&dp);

  depositCalcCore(&dp);

  ck_assert_double_eq_tol(dp.sumInterest, 605376.95, 1e-0);
  ck_assert_double_eq_tol(dp.sumEndTerm, 4123822.95, 1e-0);
  ck_assert_double_eq_tol(dp.sumTax, 49449.00, 1e-0);
}
END_TEST

Suite *suite_s21_calc_deposit(void) {
  Suite *s = suite_create("\033[45mdeposit\033[0m");
  TCase *tc_deposit = tcase_create("deposit");
  suite_add_tcase(s, tc_deposit);

  tcase_add_test(tc_deposit, deposit_1);
  tcase_add_test(tc_deposit, deposit_2);
  tcase_add_test(tc_deposit, deposit_3);
  tcase_add_test(tc_deposit, deposit_4);
  tcase_add_test(tc_deposit, deposit_5);
  tcase_add_test(tc_deposit, deposit_6);
  tcase_add_test(tc_deposit, deposit_7);
  tcase_add_test(tc_deposit, deposit_8);

  return s;
}