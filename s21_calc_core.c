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
    if (tmp) {
        (*stack) = tmp->next;
        free(tmp);
    }
}

int shuntingYard(const char* data, char* result, Priority* pr) {
    int ret = 0;
    char source[STRLEN] = {};
    strcpy(source, data);
    int numb = 0;
    int rows = STRLEN;
    int columns = STRLEN;

    strcpy(result, "");

    char** res = calloc(rows, sizeof(char*));
    for (int i = 0; i < rows; i++) {
        res[i] = calloc(columns, sizeof(char));
    }

    if (strlen(source) > 255) {
        ret = 1;
        result = NULL;
    } else {
        numb = parsSourceStr(source, res);

        for (size_t i = 0; i < STRLEN; i++) {
            printf("-->%s\n", res[i]);
        }
        if (verification(res, numb)) {
            if (parsTokenArr(res, result, numb, pr)) ret = 1;
        } else {
            result = NULL;
            ret = 1;
        }
    }

    for (int i = 0; i < rows; i++) free(res[i]);
    free(res);

    return ret;
}

void initPriority(Priority* pr) {
    // pr->priority = calloc(STRLEN, sizeof(int));
    for (int i = 0; i < STRLEN; i++) {
        pr->priority[i] = 0;
    }
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
    Stack* stack = NULL;
    Stack* stackPrior = NULL;
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
                while (stackNum && stack->priority >= prior && prior != 5) {
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
            while (stackNum != 0 && stack->priority != 1) {
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

            if (stackNum && stack->priority == 7) {
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

    return ret;
}

void calcPriorityNum(Stack** calc, int priority, char* token, double x) {
    if (!strcmp(token, "x") || !strcmp(token, "X")) {
        stackPush(calc, token, priority, x);
    } else {
        stackPush(calc, token, priority, atof(token));
    }
}

int calcPriorityOp(Stack** calc, char* token, char** str, double* result) {
    double tmp = (*calc)->value;
    char op[255] = {};
    int ret = 0;

    *result = (*calc)->next->value;
    if (!strcmp(token, "+")) {
        *result += tmp;
    } else if (!strcmp(token, "-")) {
        *result -= tmp;
    } else if (!strcmp(token, "*")) {
        *result *= tmp;
    } else if (!strcmp(token, "/")) {
        if (fabs(tmp) <= S21_EPS) {
            (*str) = NULL;
            *result = NAN;
            destroyStack(calc);
            ret = 1;
        } else {
            *result /= tmp;
        }
    } else if (!strcmp(token, "%") || !strcmp(token, "mod")) {
        *result = (long)(*result) % (long)tmp;
    } else if (!strcmp(token, "^")) {
        *result = pow(*result, tmp);
    }
    if (!ret) {
        stackPop(calc);
        stackPop(calc);
        stackPush(calc, op, 0, *result);
    }

    return ret;
}

int calcPriorityFunc(Stack** calc, char* token, char** str, double* result) {
    double tmp = (*calc)->value;
    char op[255] = {};
    int ret = 0;

    if (!strcmp(token, "+")) {
        *result = tmp;
    } else if (!strcmp(token, "-")) {
        *result = -tmp;
    } else if (!strcmp(token, "sin")) {
        *result = sin(tmp);
    } else if (!strcmp(token, "cos")) {
        *result = cos(tmp);
    } else if (!strcmp(token, "tan")) {
        if (fabs(fmod(tmp, S21_PI / 2.)) > 1.570796)
            ret = calcBadInput(calc, result, str);
        else
            *result = tan(tmp);
    } else if (!strcmp(token, "acos")) {
        if (tmp > 1. || tmp < -1.)
            ret = calcBadInput(calc, result, str);
        else
            *result = acos(tmp);
    } else if (!strcmp(token, "asin")) {
        if (tmp > 1. || tmp < -1.)
            ret = calcBadInput(calc, result, str);
        else
            *result = asin(tmp);
    } else if (!strcmp(token, "atan")) {
        *result = atan(tmp);
    } else if (!strcmp(token, "sqrt")) {
        if (tmp < 0)
            ret = calcBadInput(calc, result, str);
        else
            *result = sqrt(tmp);
    } else if (!strcmp(token, "ln")) {
        if (tmp <= 0.)
            ret = calcBadInput(calc, result, str);
        else
            *result = log(tmp);
    } else if (!strcmp(token, "log")) {
        if (tmp <= 0.)
            ret = calcBadInput(calc, result, str);
        else
            *result = log10(tmp);
    }
    if (!ret) {
        stackPop(calc);
        stackPush(calc, op, 0, *result);
    }

    return ret;
}

int calcBadInput(Stack** calc, double* result, char** str) {
    (*str) = NULL;
    *result = NAN;
    destroyStack(calc);
    return 1;
}

double calcStack(char** str, Priority* pr, double x) {
    double result = 0;
    Stack* calc = NULL;
    char* token = 0;
    char source[STRLEN] = {};

    strcpy(source, (*str));
    token = strtok(source, " ");
    for (int i = 0; i < pr->tokenNumb; i++) {
        if (pr->priority[i] == 0) {
            calcPriorityNum(&calc, pr->priority[i], token, x);
        } else if (pr->priority[i] >= 3 && pr->priority[i] <= 5) {
            if (calcPriorityOp(&calc, token, str, &result)) break;
        } else if (pr->priority[i] == 6 || pr->priority[i] == 7) {
            if (calcPriorityFunc(&calc, token, str, &result)) break;
        }
        token = strtok(NULL, " ");
    }
    if ((*str)) {
        result = calc->value;
        stackPop(&calc);
    }

    return result;
}

void destroyStack(Stack** st) {
    while ((*st)) {
        stackPop(st);
    }
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

        if (missingAfterOperation(arr, i) || verificationOfBinary(arr)) {
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

int verificationOfBinary(char** arr) {
    int ret = 0;
    char binarOp[][STRLEN] = {"mod", "/", "*", "%", "^"};

    for (size_t i = 0; i < SIZE_ARR(binarOp); i++) {
        if (!strcmp(arr[0], binarOp[i])) {
            ret = 1;
            break;
        }
    }

    return ret;
}

int missingAfterOperation(char** arr, int i) {
    int ret = 0;

    char operations[][STRLEN] = {"sin",  "cos", "tan", "acos", "asin", "atan",
                                 "sqrt", "ln",  "log", "mod",  "+",    "-",
                                 "/",    "*",   "%",   "^"};

    char binarOp[][STRLEN] = {"mod", "+", "-", "/", "*", "%", "^"};

    for (size_t j = 0; j < SIZE_ARR(operations); j++) {
        for (size_t k = 0; k < SIZE_ARR(binarOp); k++) {
            if (!strcmp(arr[i], operations[j]) &&
                (!strcmp(arr[i + 1], "") || !strcmp(arr[i + 1], binarOp[k])))
                ret = 1;
        }
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
    char operations[][STRLEN] = {"mod", ")", "/", "*", "%", "^"};
    char func[][STRLEN] = {"sin",  "cos",  "tan", "acos", "asin",
                           "atan", "sqrt", "ln",  "log"};

    for (size_t j = 0; j < SIZE_ARR(operations); j++) {
        ret =
            !strcmp(arr[i], "(") && !strcmp(arr[i + 1], operations[j]) ? 1 : 0;
        if (ret) break;
    }
    if (!ret) {
        for (size_t j = 0; j < SIZE_ARR(func); j++) {
            ret = !strcmp(arr[i], ")") && !strcmp(arr[i + 1], func[j]) ? 1 : 0;
            if (ret) break;
        }
    }

    return ret;
}

int verificationOfNumb(char** arr, int i) {
    int tokenStatus = 0;
    int wasDot = 0;

    for (size_t k = 0; k < strlen(arr[i]); k++) {
        if ((arr[i][k] >= '0' && arr[i][k] <= '9') || arr[i][k] == '.' ||
            arr[i][k] == ',') {
            if (arr[i][k] == '.' || arr[i][k] == ',') wasDot++;
            if (wasDot > 1) {
                tokenStatus = 0;
                break;
            }
            tokenStatus = 1;
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
    char sep[20] = " ()+-/*^%";

    while (*ptr != '\0') {
        if (isSep(ptr, sep)) {
            if (*ptr != ' ') {
                parsArr[numb][0] = *ptr;
                parsArr[numb][1] = '\0';
                numb++;
            }
            ptr++;
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

int isSep(char* ptr, char* sep) {
    int ret = 0;
    for (size_t i = 0; i < strlen(sep); i++) {
        if (*ptr == sep[i]) {
            ret = 1;
        }
    }
    return ret;
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
    calcPercentMonthSum(cr);

    cr->monthlyPayment = cr->mainMonthSum + cr->percentMonthSum;

    cr->totalCredit -= cr->mainMonthSum;

    cr->overpaymentOnCredit += cr->percentMonthSum;

    cr->totalPayment += cr->monthlyPayment;
}

void calcPercentMonthSum(Credit* cr) {
    double daysYear = 365.;

    if (cr->leapYear) daysYear = 366.;

    if (cr->leapYear != cr->nextLeapYear) {
        if (cr->leapYear) {
            cr->percentMonthSum =
                (cr->totalCredit * cr->interestRate / 100 *
                 (double)(cr->date - cr->days)) /
                    366. +
                (double)cr->days * (cr->totalCredit * cr->interestRate / 100) /
                    365.;
        } else {
            cr->percentMonthSum =
                (cr->totalCredit * cr->interestRate / 100 *
                 (cr->date - cr->days)) /
                    365. +
                (double)cr->days * (cr->totalCredit * cr->interestRate / 100) /
                    366.;
        }
    } else {
        cr->percentMonthSum =
            (cr->totalCredit * cr->interestRate / 100 * cr->date) / daysYear;
    }
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

void depositCalcCore(Deposit* dp) {
    double interestTemp = 0.;
    double taxTemp = 0.;
    int daysInMonth = 0;
    int month = 0;

    initialDp(dp);

    dp->sumEndTerm = dp->depositAmount;

    dp->minimumBalance = 0.;

    for (int i = 0; i < dp->periodOfPlacement; i++) {
        dp->leapYear = isLeapYear(dp, i);
        dp->nextLeapYear = isLeapYear(dp, i + 1);
        daysInMonth = (dp->currentMoth + i) % 12;
        month = daysInMonth;
        dateCorrect(&daysInMonth, dp->leapYear);

        dp->currentInterest = everyMonthCapital(dp, daysInMonth);
        interestTemp += dp->currentInterest;

        addToAmount(dp, i);
        remAmount(dp, i);

        depositPayments(dp, &interestTemp, &taxTemp, month, i);
    }

    dp->sumEndTerm = dp->depositAmount;
}

void depositPayments(Deposit* dp, double* interestTemp, double* taxTemp,
                     int month, int i) {
    if (dp->paymentsType == EVERY_MONTH) {
        addingTemp(dp, interestTemp, taxTemp);
    } else if (dp->paymentsType == EVERY_HALF_YEAR) {
        if ((i > 0 && (month == dp->currentMoth - 1 ||
                       month == (dp->currentMoth + 5) % 12)) ||
            i == dp->periodOfPlacement - 1) {
            addingTemp(dp, interestTemp, taxTemp);
        }
    } else if (dp->paymentsType == EVERY_YEAR) {
        if ((i > 0 && ((dp->currentMoth + i) % 12) == dp->currentMoth - 1) ||
            i == dp->periodOfPlacement - 1) {
            addingTemp(dp, interestTemp, taxTemp);
        }
    } else if (dp->paymentsType == END_TERM) {
        if (i == dp->periodOfPlacement - 1) {
            addingTemp(dp, interestTemp, taxTemp);
        }
    }
    if ((i > 0 && (((dp->currentMoth + i) % 12) == 11)) ||
        i == dp->periodOfPlacement - 1) {
        dp->sumTax += taxRateCalc(dp, *taxTemp);
        *taxTemp = 0.;
    }
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
        } else if (dp->listPartialWithdrawals[i].term == EVERY_HALF_YEAR) {
            if (counter > 0 && (month == dp->currentMoth - 1 ||
                                month == (dp->currentMoth + 5) % 12)) {
                remAmountEveryTime(dp, i);
            }
        } else if (dp->listPartialWithdrawals[i].term == EVERY_YEAR) {
            if (counter > 0 && month == dp->currentMoth - 1) {
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

double everyMonthCapital(Deposit* dp, int daysInMonth) {
    double profit = 0.;
    double daysInYear = 0.;
    daysInYear = dp->leapYear ? 366. : 365.;

    if (dp->leapYear != dp->nextLeapYear) {
        if (dp->leapYear) {
            profit = dp->depositAmount * (dp->interestRate / 100.) / 366. *
                         ((double)daysInMonth - dp->currentDay) +
                     dp->currentDay *
                         ((dp->interestRate / 100.) * dp->depositAmount / 365.);
        } else {
            profit = dp->depositAmount * (dp->interestRate / 100.) / 365. *
                         ((double)daysInMonth - dp->currentDay) +
                     dp->currentDay *
                         ((dp->interestRate / 100.) * dp->depositAmount / 366.);
        }
    } else {
        profit = dp->depositAmount * (dp->interestRate / 100.) / daysInYear *
                 (double)daysInMonth;
    }

    return profit;
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
