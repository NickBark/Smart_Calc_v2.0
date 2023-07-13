#ifndef DEPOSITCALC_H
#define DEPOSITCALC_H

#include "dependencies.hpp"

class DepositCalc : public QFrame {
  Q_OBJECT
 public:
  explicit DepositCalc(QFrame* parent = nullptr);

  void Designer();
  void Properties();
  void Layouts();
  void Connector();

  QGridLayout* glDep;

  QLabel* lDepAmount;
  QDoubleSpinBox* dsDepAmount;

  QLabel* lPeriodOfPlacement;
  QSpinBox* sPeriodOfPlacement;

  QLabel* lInterestRate;
  QDoubleSpinBox* dsInterestRate;

  QLabel* lTaxRate;
  QDoubleSpinBox* dsTaxRate;

  QLabel* lPerOfPay;
  QComboBox* cmPerOfPay;

  QLabel* lStartDate;
  QSpinBox* sbStartDateDay;
  QSpinBox* sbStartDateMonth;
  QSpinBox* sbStartDateYear;

  QLabel* lCapital;
  QCheckBox* cbCapital;

  QPushButton* pbAddMoney;
  QFrame* fAddMoney;
  QVBoxLayout* vblAddM;
  QGridLayout* glAddM;
  QPushButton* pbPlusAddM;
  QPushButton* pbMinusAddM;
  QComboBox* cbAdd;
  QTableWidget* twAdd;
  QPushButton* pbCloseAdd;
  int rowsAdd;

  QPushButton* pbRemMoney;
  QFrame* fRemMoney;
  QVBoxLayout* vblRemM;
  QGridLayout* glRemM;
  QPushButton* pbPlusRemM;
  QPushButton* pbMinusRemM;
  QTableWidget* twRem;
  QPushButton* pbCloseRem;

  QPushButton* pbCalc;

  // output
  QFrame* output;
  QVBoxLayout* vblOut;
  QLabel* sumInterest;
  QLabel* sumEndTerm;
  QLabel* sumTax;
  QPushButton* pbCloseOut;

 private slots:
  void slotCalc();
  void slotCloseOut();

  void slotAddM();
  void slotRemM();

  void slotCloseAdd();
  void slotCloseRem();

  void slotPlusAdd();
  void slotMinusAdd();
  void slotPlusRem();
  void slotMinusRem();

  void setStartDay();

 signals:
};

#endif  // DEPOSITCALC_H
