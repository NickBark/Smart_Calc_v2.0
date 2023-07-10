#ifndef CORE_H
#define CORE_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define STRLEN 255
#define SIZE_OF_CORRECT 21
#define S21_PI 3.14159265358979323846
#define S21_EPS 1e-8
#define SIZE_ARR(var) sizeof(var) / sizeof(var[0])

typedef struct Point {
    double x;   // функциональный X
    double y;   // функциональный Y
    double ix;  // оконный X
    double jy;  // оконный Y
    int error;  // ошибочная точка (1 - ошибка, 0 - ОК)
} Point;

typedef struct Stack {
    char* data;
    int priority;
    double value;
    struct Stack* next;
} Stack;

typedef struct Priority {
    int* priority;
    int tokenNumb;
} Priority;

typedef struct Credit {
    double totalCredit;
    double term;
    int date;
    double interestRate;
    unsigned int type;
    double monthlyPayment;
    double overpaymentOnCredit;
    double totalPayment;
    double mainMonthSum;
    double percentMonthSum;
    int leapYear;
} Credit;

typedef struct AddMoney {
    int term;
    double money;
} AddMoney;

typedef struct RemMoney {
    int term;
    double money;
} RemMoney;

typedef struct Deposit {
    double depositAmount;        // сумма вклада
    double periodOfPlacement;    // срок размещния
    double interestRate;         // процентная ставка
    double taxRate;              // налоговая ставка
    int periodOfPayments;        // периодичность выплат
    int interestCapitalization;  // капитализация процентов

    AddMoney replenishmentList[255];  // список пополнений
    int addCount;
    RemMoney listPartialWithdrawals[255];  // список частичных снятий
    int remCount;
    double minimumBalance;

    int paymentsType;

    double currentInterest;

    int currentMoth;
    int currentYear;
    int currentDay;
    int leapYear;
    int nextLeapYear;

    double taxArr[255];
    int countTaxArr;

    double sumInterest;
    double sumTax;
    double sumEndTerm;
} Deposit;

enum Dates {
    JANUARY = 1,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER = 0
};

enum PaymentsPeriod {
    EVERY_MONTH,
    // EVERY_QUARTER,
    EVERY_HALF_YEAR,
    EVERY_YEAR,
    END_TERM
};

// Функции стека
Stack* createNode(char* data, int priority, double value);
void stackPush(Stack** stack, char* data, int priority, double value);
void stackPop(Stack** stack);

// Алгоритм Дейкстры ("сортировочная станция")
int shuntingYard(const char* data, char* result, Priority* pr);
// Вычисления
int calcus(char* result, Priority* pr, double x, double* answer);

// Доп
void printArr(char** arr, int numb);
int isSep(char* ptr, char* sep);
int parsSourceStr(char* source, char** parsArr);

int verification(char** arr, int numb);
int verificationOfNumb(char** arr, int i);
int verificationOfOperation(char** arr, int i);
int missingOperation(char** arr, int i);
int missingAfterOperation(char** arr, int i);
// int bracketsIsEmpty(char** arr, int i);
int bracketsError(char** arr, int i);

int parsTokenArr(char** arr, char* resultStr, int tokenNum, Priority* pr);
int priority(char* str, int uno);
void stackPriority(Stack** stackPrior, char** arr, int tokenNum);
int isOp(char* str);
double calcStack(char** str, Priority* pr, double x);
void printStack(Stack* stack, int count);
void bubbleSort(double* arr, int num);
int removeDuplicate(double* arr, double* newArr, int num);
void initPriority(Priority* pr);

// Функции для кредитного калькулятора
void creditCalcCore(Credit* cr);
void annuity(Credit* cr);
void differentiated(Credit* cr);

// Функции для депозитного калькулятора
void depositCalcCore(Deposit* dp);
void initialDp(Deposit* dp);
double taxRateCalc(Deposit* dp, double accum);
void everyYearType(Deposit* dp, double* depositDays, int daysInMonth,
                   int yearTmp, double daysInYear);
double everyMonthCapital(Deposit* dp, int daysInMonth, int month);
int isLeapYear(Deposit* dp, int i);
int isLeap(int year);
void addToAmount(Deposit* dp, int counter);
void remAmount(Deposit* dp, int counter);
void addingTemp(Deposit* dp, double* interestTemp, double* taxTemp);
void remAmountEveryTime(Deposit* dp, int num);
void addAmountEveryTime(Deposit* dp, int num);

// Вспомогательные фукнции финансовых калькуляторов
void dateCorrect(int* date, int leapYear);

#endif  // CORE_H
