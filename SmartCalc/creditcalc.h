#ifndef CREDITCALC_H
#define CREDITCALC_H

#include "dependencies.hpp"

class CreditCalc : public QFrame {
    Q_OBJECT
   public:
    explicit CreditCalc(QFrame* parent = nullptr);

    void Designer();
    void Properties();
    void Layouts();
    void Connector();

    //    double* monthlyPaymentArr;
    Credit cr;

    QGridLayout* glButtons;
    QPushButton* pbResult;

    QDoubleSpinBox* dsbSum;
    QSpinBox* sbTime;
    QDoubleSpinBox* dsbPersent;
    QComboBox* cmType;
    QComboBox* cmDate;
    QLabel* lTime;
    QLabel* lPersent;
    QLabel* lSum;

    QLabel* lStartDate;
    QSpinBox* sbStartDateDay;
    QSpinBox* sbStartDateMonth;
    QSpinBox* sbStartDateYear;

    //-----OUTPUT_ANN-----
    QFrame* outputAnn;
    QGridLayout* glOutAnn;
    QLabel* lMonthlyPayment;
    QLabel* lOverpayment;
    QLabel* lTotalPayment;
    QPushButton* pbCloseAnn;

    //-----OUTPUT_DIFF-----
    QFrame* outputDiff;
    QVBoxLayout* hblOutDiff;
    QLabel* lMonthlyPaymentDiff;
    QGridLayout* glOutDiff;
    QLabel* lOverpaymentDiff;
    QLabel* lTotalPaymentDiff;
    QPushButton* pbCloseDiff;
    QScrollArea* saDiff;

    void dateToString(int date, QString* strDate);

   signals:

   private slots:
    void slotPbResult();
    void slotPbCloseAnn();
    void slotPbCloseDiff();

    void setStartDay();
};

#endif  // CREDITCALC_H
