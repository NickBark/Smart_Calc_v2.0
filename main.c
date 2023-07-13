#include "s21_calc_core.h"
#include "tests/unit.h"

// заранее расставить приоритет унарных операторов
// передавать в функцию priority указатель на стек (делать через два стека)

// ВАЖНО
//// Обработать деление на 0
////// Cделано, надо тестить

//// Обработать возведение в степень (a^b^c = a^(b^c))
////// Сделано, надо тестить

// ОШИБКИ
//// Не корректно конвертирует точку из qt в ядро, надо обрабатывать запятую

// int foo() {
//   Deposit dp;
//   initialDp(&dp);
//   dp.depositAmount = 100000;
//   dp.interestRate = 8.;

//   // printf("profit: %lf\n", everyMonthCapital(&dp, 30, ));
// }

void foo2() {
    char str[255] = {"1,,5+3,5"};
    char result[255] = {};
    Priority pr = {};
    initPriority(&pr);
    printf("sh:%d\n", shuntingYard(str, result, &pr));
    // free(pr.priority);
}

void foo3() {
    Deposit dp;
    dp.depositAmount = 3500000.;
    dp.periodOfPlacement = 9.;
    dp.interestRate = 8.;
    dp.taxRate = 13.;
    dp.paymentsType = 0;
    dp.interestCapitalization = 0;
    dp.currentMoth = 7;
    dp.currentYear = 2023;
    dp.addCount = 0;
    dp.remCount = 0;

    initialDp(&dp);

    depositCalcCore(&dp);

    printf("sumI:%.2lf\n", dp.sumInterest);
    printf("sumE:%.2lf\n", dp.sumEndTerm);
    printf("sumT:%.2lf\n", dp.sumTax);
}

void foo4() {
    char str[255] = {"1.5(())+3.5(())"};
    char result[255] = {};
    Priority pr = {};
    initPriority(&pr);
    printf("sh:%d\n", shuntingYard(str, result, &pr));
    // free(pr.priority);
}

void foo5() {
    char str[255] = {
        "             1              +                        3                "
        "          "};
    char result[255] = {};
    double answer = 0.;
    Priority pr = {};
    initPriority(&pr);
    printf("sh:%d\n", shuntingYard(str, result, &pr));

    calcus(result, &pr, 1, &answer);

    printf("answer:%lf\n", answer);
    // free(pr.priority);
}

int main() {
    // foo();
    foo5();
    // printf("%lf", asin(1));

    // foo3();
    // for (size_t i = 0; i < 20; i++) {
    //     printf("%d\n", foo());
    // }

    // Credit* cr = malloc(sizeof(Credit));
    // cr->term = 36;
    // cr->date = 28;
    // cr->totalCredit = 120000;
    // cr->type = 1;
    // cr->interestRate = 12;

    // creditCalcCore(cr);

    // printf("%lf\n%lf\n%lf\n", cr->monthlyPayment, cr->overpaymentOnCredit,
    //        cr->totalPayment);
    // Массив со строкой для поиска
    // char s1[240] = "2^(2^(1^3))^5";
    // char s12[240] = "32.523+523.235";
    // double ans = 0;
    // // char s2[240] = {};
    // char* s2 = calloc(255, sizeof(char));

    // printf("ret: %d\n", shuntingYard(s12, s2, &ans, 7));
    // printf("ans: %lf\n", ans);

    // // for (int i = 0; i < 100; i++) {

    // // }

    // free(s2);

    // double ppp[5] = {2, 2, 4, 5, 3};
    // double qqq[5] = {};
    // int new = 0;
    // new = removeDuplicate(ppp, qqq, 5);

    // // Набор символов, которые должны входить в искомый сегмент
    // // char s2[10] = "+";
    // // printf("%s\n", strtok(s1, s2));

    // // Разделители
    // char sep[10] = " +-/%%";
    // // Переменная, в которую будут заноситься начальные адреса частей
    // // строки str
    // char *istr;

    // // Выделение первой части строки
    // istr = strtok(s1, sep);

    // // Выделение последующих частей
    // while (istr != NULL) {
    //     // Вывод очередной выделенной части
    //     printf("%s\n", istr);
    //     // Выделение очередной части строки
    //     istr = strtok(NULL, sep);
    // }

    return 0;
}