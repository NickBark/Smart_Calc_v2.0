#include "s21_calc_core.h"

Stack* createNode(char* data, int priority, double value) {
    Stack* node = (Stack*)malloc(sizeof(Stack));
    if (!node) {
        exit(1);
    }
    node->data = data;
    node->priority = priority;
    node->value = value;
    node->next = NULL;

    return node;
}

void stackPush(Stack** stack, char* data, int priority, double value) {
    Stack* newNode = createNode(data, priority, value);
    if (!(*stack)) {
        (*stack) = newNode;
    } else {
        newNode->next = (*stack);
        (*stack) = newNode;
    }
}

void stackPop(Stack** stack) {
    Stack* tmp = (*stack);
    (*stack) = (*stack)->next;
    free(tmp);
}

int shuntingYard(const char* data, char* result, Priority* pr) {
    int ret = 0;
    char source[STRLEN] = {};
    strcpy(source, data);
    int numb = 0;
    int rows = 255;
    int columns = 255;

    strcpy(result, "");

    char** res = calloc(rows, sizeof(char*));
    for (int i = 0; i < rows; i++) {
        res[i] = calloc(columns, sizeof(char));
    }

    numb = parsSourceStr(source, res);

    // for (int i = 0; i < rows; i++) {
    //     fprintf(stderr, "%s\n", res[i]);
    // }

    if (verification(res, numb)) {
        if (parsTokenArr(res, result, numb, pr)) ret = 1;
    } else {
        // fprintf(stderr, "ERROR = bad input\n");
        result = NULL;
        ret = 1;
    }

    for (int i = 0; i < rows; i++) free(res[i]);
    free(res);

    return ret;
}

void initPriority(Priority* pr) {
    pr->priority = calloc(STRLEN, sizeof(int));
    pr->tokenNumb = 0;
}

int calcus(char* result, Priority* pr, double x, double* answer) {
    int ret = 0;
    *answer = calcStack(&result, pr, x);
    if (!result) {
        // fprintf(stderr, "ERROR = div by zero or something else\n");
        ret = 1;
    }

    return ret;
}

int parsTokenArr(char** arr, char* resultStr, int tokenNum, Priority* pr) {
    int ret = 0;
    Stack* stack = calloc(STRLEN, sizeof(Stack));
    Stack* stackPrior = calloc(STRLEN, sizeof(Stack));
    int stackNum = 0;
    int prior = 0;

    stackPriority(&stackPrior, arr, tokenNum);

    for (int i = 0; i < tokenNum; i++) {
        prior = stackPrior->priority;
        stackPop(&stackPrior);

        if (prior == 0) {
            strcat(resultStr, arr[i]);
            strcat(resultStr, " ");
            pr->priority[pr->tokenNumb++] = prior;
        } else if (prior == 1 || prior == 7) {
            stackPush(&stack, arr[i], prior, 0);
            stackNum++;
        } else if (prior >= 3 && prior <= 6) {
            if (stackNum) {
                // не равен 5 (pow), потому что степень считается справа на лево
                while (stack->priority >= prior && prior != 5) {
                    strcat(resultStr, stack->data);
                    strcat(resultStr, " ");
                    pr->priority[pr->tokenNumb++] = stack->priority;
                    stackPop(&stack);
                    stackNum--;
                }
            }
            stackPush(&stack, arr[i], prior, 0);
            stackNum++;
        } else if (prior == 2) {
            while (stack->priority != 1 && stackNum != 0) {
                strcat(resultStr, stack->data);
                strcat(resultStr, " ");
                pr->priority[pr->tokenNumb++] = stack->priority;
                stackPop(&stack);
                stackNum--;
            }
            if (stackNum) {
                stackPop(&stack);
                stackNum--;
            } else {
                fprintf(stderr, "ERROR = not correct\n");
                ret = 1;
            }

            if (stack->priority == 7) {
                strcat(resultStr, stack->data);
                strcat(resultStr, " ");
                pr->priority[pr->tokenNumb++] = stack->priority;
                stackPop(&stack);
                stackNum--;
            }
        }
        if (i == (tokenNum - 1)) {
            while (stackNum) {
                if (stack->priority == 1 || stack->priority == 2) {
                    ret = 1;
                    fprintf(stderr, "ERROR = not correct\n");
                }
                strcat(resultStr, stack->data);
                strcat(resultStr, " ");
                pr->priority[pr->tokenNumb++] = stack->priority;
                stackPop(&stack);
                stackNum--;
            }
        }
    }

    strcat(resultStr, "\0");

    free(stack);
    free(stackPrior);

    return ret;
}

double calcStack(char** str, Priority* pr, double x) {
    double result = 0;
    Stack* calc = calloc(STRLEN, sizeof(Stack));
    char* token = 0;
    char source[STRLEN] = {};
    double tmp = 0;
    char op[255] = {};

    strcpy(source, (*str));
    token = strtok(source, " ");
    for (int i = 0; i < pr->tokenNumb; i++) {
        if (pr->priority[i] == 0) {
            if (!strcmp(token, "x") || !strcmp(token, "X")) {
                stackPush(&calc, token, pr->priority[i], x);
            } else {
                stackPush(&calc, token, pr->priority[i], atof(token));
            }
        } else if (pr->priority[i] >= 3 && pr->priority[i] <= 5) {
            tmp = calc->value;
            result = calc->next->value;
            if (!strcmp(token, "+")) {
                result += tmp;
            } else if (!strcmp(token, "-")) {
                result -= tmp;
            } else if (!strcmp(token, "*")) {
                result *= tmp;
            } else if (!strcmp(token, "/")) {
                if (fabs(tmp) <= S21_EPS) {
                    (*str) = NULL;
                    result = NAN;
                    break;
                }
                result /= tmp;
            } else if (!strcmp(token, "%") || !strcmp(token, "mod")) {
                result = (long)result % (long)tmp;
            } else if (!strcmp(token, "^")) {
                result = pow(result, tmp);
            }
            stackPop(&calc);
            stackPop(&calc);
            stackPush(&calc, op, 0, result);
        } else if (pr->priority[i] == 6 || pr->priority[i] == 7) {
            tmp = calc->value;
            if (!strcmp(token, "+")) {
                result = tmp;
            } else if (!strcmp(token, "-")) {
                result = -tmp;
            } else if (!strcmp(token, "sin")) {
                result = sin(tmp);
            } else if (!strcmp(token, "cos")) {
                result = cos(tmp);
            } else if (!strcmp(token, "tan")) {
                if (fabs(fmod(tmp, S21_PI / 2.)) > 1.570796) {
                    (*str) = NULL;
                    break;
                }

                // if (fabs(fmod(tmp, S21_PI)) == S21_PI / 2.) {
                //     (*str) = NULL;
                //     break;
                // }
                result = tan(tmp);
            } else if (!strcmp(token, "acos")) {
                if (tmp > 1. || tmp < -1.) {
                    (*str) = NULL;
                    break;
                }
                result = acos(tmp);
            } else if (!strcmp(token, "asin")) {
                if (tmp > 1. || tmp < -1.) {
                    (*str) = NULL;
                    break;
                }
                result = asin(tmp);
            } else if (!strcmp(token, "atan")) {
                result = atan(tmp);
            } else if (!strcmp(token, "sqrt")) {
                result = sqrt(tmp);
            } else if (!strcmp(token, "ln")) {
                if (tmp <= 0.) {
                    (*str) = NULL;
                    break;
                }
                result = log(tmp);
            } else if (!strcmp(token, "log")) {
                if (tmp <= 0.) {
                    (*str) = NULL;
                    break;
                }
                result = log10(tmp);
            }
            stackPop(&calc);
            stackPush(&calc, op, 0, result);
        }
        token = strtok(NULL, " ");
    }
    if ((*str)) {
        result = calc->value;
        stackPop(&calc);
    }
    free(calc);

    return result;
}

void stackPriority(Stack** stackPrior, char** arr, int tokenNum) {
    for (int i = tokenNum - 1; i >= 0; i--) {
        if (!strcmp(arr[i], "+") || !strcmp(arr[i], "-")) {
            if (i == 0 || !strcmp(arr[i - 1], "(") || isOp(arr[i - 1])) {
                stackPush(stackPrior, arr[i], priority(arr[i], 1), 0);
                continue;
            }
        }
        stackPush(stackPrior, arr[i], priority(arr[i], 0), 0);
    }
}

int isOp(char* str) {
    return !strcmp(str, "+") || !strcmp(str, "-") || !strcmp(str, "/") ||
           !strcmp(str, "*") || !strcmp(str, "%") || !strcmp(str, "mod");
}

int priority(char* str, int uno) {
    int ret = 0;

    char func[9][STRLEN] = {
        "sin", "cos", "tan", "acos", "asin", "atan", "sqrt", "ln", "log",
    };

    if (uno) {
        ret = 6;
    } else if (!strcmp(str, " ")) {
        ret = -1;
    } else if (!strcmp(str, "(")) {
        ret = 1;
    } else if (!strcmp(str, ")")) {
        ret = 2;
    } else if (!strcmp(str, "+") || !strcmp(str, "-")) {
        ret = 3;
    } else if (!strcmp(str, "*") || !strcmp(str, "/") || !strcmp(str, "%") ||
               !strcmp(str, "mod")) {
        ret = 4;
    } else if (!strcmp(str, "^")) {
        ret = 5;
    } else {
        for (int i = 0; i < 9; i++) {
            if (!strcmp(str, func[i])) {
                ret = 7;  // функция
                break;
            }
        }
    }

    return ret;
}

// 1 = OK
// 0 = FALSE
int verification(char** arr, int numb) {
    int tokenStatus = 0;

    for (int i = 0; i < numb; i++) {
        if (*arr[i] == 0) break;
        tokenStatus = verificationOfOperation(arr, i);
        if (missingAfterOperation(arr, i)) {
            tokenStatus = 0;
        } else {
            if (!tokenStatus) {
                tokenStatus = verificationOfNumb(arr, i);
                if (tokenStatus) tokenStatus = missingOperation(arr, i) ? 0 : 1;
            }
        }
        if (!tokenStatus) {
            break;
        }
    }
    return tokenStatus;
}

int missingAfterOperation(char** arr, int i) {
    int ret = 0;

    char operations[][STRLEN] = {"sin",  "cos", "tan", "acos", "asin", "atan",
                                 "sqrt", "ln",  "log", "mod",  "+",    "-",
                                 "/",    "*",   "%",   "^"};

    for (size_t j = 0; j < SIZE_ARR(operations); j++) {
        if (!strcmp(arr[i], operations[j]) && !strcmp(arr[i + 1], "")) ret = 1;
    }

    return ret;
}

int missingOperation(char** arr, int i) { return !strcmp(arr[i + 1], "("); }

int verificationOfOperation(char** arr, int i) {
    int tokenStatus = 0;

    char correct[SIZE_OF_CORRECT][STRLEN] = {
        "sin", "cos", "tan", "acos", "asin", "atan", "sqrt",
        "ln",  "log", "mod", "(",    ")",    "+",    "-",
        "/",   "*",   "%",   "x",    "X",    " ",    "^"};

    for (int j = 0; j < SIZE_OF_CORRECT; j++) {
        if (!strcmp(arr[i], correct[j])) {
            if (bracketsError(arr, i))
                tokenStatus = 0;
            else
                tokenStatus = 1;
            break;
        }
    }

    return tokenStatus;
}

int bracketsError(char** arr, int i) {
    int ret = 0;
    char operations[6][STRLEN] = {"mod", ")", "/", "*", "%", "^"};

    for (int j = 0; j < 6; j++) {
        ret =
            !strcmp(arr[i], "(") && !strcmp(arr[i + 1], operations[j]) ? 1 : 0;
        if (ret) break;
    }

    return ret;
}

// int bracketsIsEmpty(char** arr, int i) {
//     return !strcmp(arr[i], "(") && !strcmp(arr[i + 1], ")");
// }

int verificationOfNumb(char** arr, int i) {
    int tokenStatus = 0;

    for (size_t k = 0; k < strlen(arr[i]); k++) {
        if ((arr[i][k] >= '0' && arr[i][k] <= '9') || arr[i][k] == '.' ||
            arr[i][k] == ',') {
            if ((arr[i][k] == '.' && arr[i][k + 1] == '.') ||
                (arr[i][k] == ',' && arr[i][k + 1] == ',')) {
                tokenStatus = 0;
                break;
            } else {
                tokenStatus = 1;
            }
        } else {
            tokenStatus = 0;
            break;
        }
    }

    return tokenStatus;
}

// Возвращает количество токенов
int parsSourceStr(char* source, char** parsArr) {
    int numb = 0;
    char* ptr = source;
    // Разделители
    char sep[20] = " ()+-/*x^%";

    while (*ptr != '\0') {
        if (isSep(ptr, sep)) {
            parsArr[numb][0] = *ptr;
            parsArr[numb][1] = '\0';
            ptr++;
            numb++;
        } else {
            int i = 0;
            for (; *ptr != '\0' && !isSep(ptr, sep); i++) {
                parsArr[numb][i] = *ptr++;
            }
            parsArr[numb][i] = '\0';
            numb++;
        }
    }

    return numb;
}

void printArr(char** arr, int numb) {
    for (int i = 0; i < numb; i++) {
        for (size_t j = 0; j < strlen(arr[i]); j++) {
            printf("%c", arr[i][j]);
        }
        printf("\n");
    }
}

int isSep(char* ptr, char* sep) {
    int ret = 0;
    for (size_t i = 0; i < strlen(sep); i++) {
        if (*ptr == sep[i]) {
            ret = 1;
        }
    }
    return ret;
}

void printStack(Stack* stack, int count) {
    for (int i = 0; i < count; i++) {
        printf("stack: %s\n", stack->data);
        stackPop(&stack);
    }
}

void bubbleSort(double* arr, int num) {
    double tmp;
    int exit = 1;

    while (exit) {
        for (int i = 0; i < num - 1; i++) {
            if (arr[i] <= arr[i + 1]) {
                exit = 0;
            } else {
                tmp = arr[i + 1];
                arr[i + 1] = arr[i];
                arr[i] = tmp;
                exit = 1;
                break;
            }
        }
    }
}

int removeDuplicate(double* arr, double* newArr, int num) {
    int newNum = 0;
    int exit = 1;
    double* current = arr;

    bubbleSort(arr, num);

    newArr[0] = arr[0];
    newNum++;

    for (int i = 1; i < num - 1; i++) {
        if (arr[i] == arr[i + 1]) continue;
        newArr[newNum++] = arr[i + 1];
    }

    return newNum;
}

void creditCalcCore(Credit* cr) {
    // if(cr->term == 0) ERROR;
    if (cr->type == 0) {
        annuity(cr);
    } else if (cr->type == 1) {
        dateCorrect(&cr->date, cr->leapYear);
        differentiated(cr);
    }
}

void annuity(Credit* cr) {
    double monthlyRate = 0.;
    monthlyRate = cr->interestRate / 1200.;
    cr->monthlyPayment = cr->totalCredit * monthlyRate /
                         (1 - pow((1 + monthlyRate), (-cr->term)));
    cr->overpaymentOnCredit = cr->monthlyPayment * cr->term - cr->totalCredit;
    cr->totalPayment = cr->totalCredit + cr->overpaymentOnCredit;
}

void differentiated(Credit* cr) {
    double daysYear = 365.;
    if (cr->leapYear) daysYear = 366.;
    cr->percentMonthSum =
        (cr->totalCredit * cr->interestRate / 100 * cr->date) / daysYear;
    cr->monthlyPayment = cr->mainMonthSum + cr->percentMonthSum;

    cr->totalCredit -= cr->mainMonthSum;

    cr->overpaymentOnCredit += cr->percentMonthSum;

    cr->totalPayment += cr->monthlyPayment;
}

void dateCorrect(int* date, int leapYear) {
    if (*date == JANUARY || *date == MARCH || *date == MAY || *date == JULY ||
        *date == AUGUST || *date == OCTOBER || *date == DECEMBER)
        *date = 31;
    else if (*date == APRIL || *date == JUNE || *date == SEPTEMBER ||
             *date == NOVEMBER)
        *date = 30;
    else if (*date == FEBRUARY && leapYear)
        *date = 29;
    else if (*date == FEBRUARY && !leapYear)
        *date = 28;
}

// dp->currentInterest и dp->sumInterest вычисляется параллельно
// друг другу, только одно прибавляется каждый раз, а второе и
// прибавляется и вычитается, если есть вычиты
// dp->currentInterest = dp->sumInterest;
// fprintf(stderr, "%lf", dp->currentInterest);

// есть общий накопленный процент, а есть процент с вычитами, от которого
// рассчитывается налог
void depositCalcCore(Deposit* dp) {
    double interestTemp = 0.;
    double taxTemp = 0.;
    int daysInMonth = 0;
    int yearTmp = 0;
    int yearTmp2 = 0;
    int month = 0;

    initialDp(dp);

    dp->sumEndTerm = dp->depositAmount;
    yearTmp = dp->currentYear;

    dp->minimumBalance = 0.;

    for (int i = 0; i < dp->periodOfPlacement; i++) {
        dp->leapYear = isLeapYear(dp, i);
        dp->nextLeapYear = isLeapYear(dp, i + 1);
        daysInMonth = (dp->currentMoth + i) % 12;
        month = daysInMonth;
        dateCorrect(&daysInMonth, dp->leapYear);
        if (!i) daysInMonth = daysInMonth - dp->currentDay + 1;
        if (i == dp->periodOfPlacement - 1)
            daysInMonth = daysInMonth + dp->currentDay - 1;

        dp->currentInterest = everyMonthCapital(dp, daysInMonth, month);
        interestTemp += dp->currentInterest;

        addToAmount(dp, i);
        remAmount(dp, i);

        if (dp->paymentsType == EVERY_MONTH) {
            addingTemp(dp, &interestTemp, &taxTemp);
        } else if (dp->paymentsType == EVERY_HALF_YEAR) {
            if ((i > 0 && (month == dp->currentMoth - 1 ||
                           month == (dp->currentMoth + 5) % 12)) ||
                i == dp->periodOfPlacement - 1) {
                addingTemp(dp, &interestTemp, &taxTemp);
            }
        } else if (dp->paymentsType == EVERY_YEAR) {
            if ((i > 0 &&
                 ((dp->currentMoth + i) % 12) == dp->currentMoth - 1) ||
                i == dp->periodOfPlacement - 1) {
                addingTemp(dp, &interestTemp, &taxTemp);
            }
        } else if (dp->paymentsType == END_TERM) {
            if (i == dp->periodOfPlacement - 1) {
                addingTemp(dp, &interestTemp, &taxTemp);
            }
        }

        if ((i > 0 && (((dp->currentMoth + i) % 12) == 11)) ||
            i == dp->periodOfPlacement - 1) {
            dp->sumTax += taxRateCalc(dp, taxTemp);
            taxTemp = 0.;
        }
    }

    dp->sumEndTerm = dp->depositAmount;
}

void addingTemp(Deposit* dp, double* interestTemp, double* taxTemp) {
    dp->sumInterest += *interestTemp;
    *taxTemp += *interestTemp;
    if (dp->interestCapitalization) dp->depositAmount += *interestTemp;
    *interestTemp = 0.;
}

void addToAmount(Deposit* dp, int counter) {
    int month = (dp->currentMoth + counter) % 12;

    for (int i = 0; i < dp->addCount; i++) {
        if (dp->replenishmentList[i].term == EVERY_MONTH) {
            addAmountEveryTime(dp, i);
        } else if (dp->replenishmentList[i].term == EVERY_HALF_YEAR) {
            if (counter > 0 && (month == dp->currentMoth - 1 ||
                                month == (dp->currentMoth + 5) % 12)) {
                addAmountEveryTime(dp, i);
            }
        } else if (dp->replenishmentList[i].term == EVERY_YEAR) {
            if (counter > 0 && month == dp->currentMoth - 1) {
                addAmountEveryTime(dp, i);
            }
        }
    }
}

void remAmount(Deposit* dp, int counter) {
    int month = (dp->currentMoth + counter) % 12;

    for (int i = 0; i < dp->remCount; i++) {
        if (dp->listPartialWithdrawals[i].term == EVERY_MONTH) {
            remAmountEveryTime(dp, i);
        } else if (dp->replenishmentList[i].term == EVERY_HALF_YEAR) {
            if (counter > 0 && (month == dp->currentMoth - 1 ||
                                month == (dp->currentMoth + 5) % 12)) {
                remAmountEveryTime(dp, i);
            }
        } else if (dp->replenishmentList[i].term == EVERY_YEAR) {
            if (counter > 0 &&
                ((dp->currentMoth + counter) % 12) == dp->currentMoth - 1) {
                remAmountEveryTime(dp, i);
            }
        }
    }
}

void addAmountEveryTime(Deposit* dp, int num) {
    dp->depositAmount += dp->replenishmentList[num].money;
}

void remAmountEveryTime(Deposit* dp, int num) {
    if (dp->depositAmount - dp->listPartialWithdrawals[num].money >=
        dp->minimumBalance)
        dp->depositAmount -= dp->listPartialWithdrawals[num].money;
}

int isLeapYear(Deposit* dp, int i) {
    return isLeap(dp->currentYear + (dp->currentMoth - 1 + i) / 12);
}

int isLeap(int year) {
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

double everyMonthCapital(Deposit* dp, int daysInMonth, int month) {
    double profit = 0.;
    double daysInYear = 0.;
    daysInYear = dp->leapYear ? 366. : 365.;

    // fprintf(stderr, "month : %d : %lf : ", month, daysInYear);

    if (dp->leapYear != dp->nextLeapYear) {
        if (dp->leapYear) {
            profit = dp->depositAmount * (dp->interestRate / 100.) / 366. *
                         ((double)daysInMonth - 1.) +
                     (dp->interestRate / 100.) * dp->depositAmount / 365.;
        } else {
            profit = dp->depositAmount * (dp->interestRate / 100.) / 365. *
                         ((double)daysInMonth - 1.) +
                     (dp->interestRate / 100.) * dp->depositAmount / 366.;
        }
    } else {
        profit = dp->depositAmount * (dp->interestRate / 100.) / daysInYear *
                 (double)daysInMonth;
    }

    // fprintf(stderr, "profit : %lf \n", profit);

    return profit;
}

void everyYearType(Deposit* dp, double* depositDays, int daysInMonth,
                   int yearTmp, double daysInYear) {
    if (daysInMonth == dp->currentMoth &&
        yearTmp !=
            dp->currentYear) {  // начисление раз в год (от текущего месяца)
        dp->currentInterest = (dp->depositAmount * dp->interestRate *
                               (*depositDays / daysInYear)) /
                              100.;
        dp->sumInterest += dp->currentInterest;
        *depositDays = 0.;
    }
}

double taxRateCalc(Deposit* dp, double accum) {
    double tax = 0.;
    double nonTaxableIncome = 75000.;  // ставка цб = 7.5%

    tax = accum - nonTaxableIncome;
    if (tax > 0.)
        tax *= (dp->taxRate / 100.);
    else
        tax = 0.;

    return tax;
}

void initialDp(Deposit* dp) {
    dp->sumEndTerm = 0.;
    dp->sumInterest = 0.;
    dp->sumTax = 0.;
    dp->leapYear = 0;
    dp->currentInterest = 0.;
    dp->countTaxArr = 0;
    for (int i = 0; i < 255; i++) {
        dp->taxArr[i] = 0.;
    }
}
