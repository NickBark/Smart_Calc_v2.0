#include "depositcalc.h"

DepositCalc::DepositCalc(QFrame *parent) : QFrame{parent} {
  this->setFixedSize(400, 400);

  Designer();
  Properties();
  Layouts();
  Connector();

  rowsAdd = 0;
}

void DepositCalc::Designer() {
  glDep = new QGridLayout(this);
  lDepAmount = new QLabel("Cумма вклада (рубли)", this);
  dsDepAmount = new QDoubleSpinBox(this);

  lPeriodOfPlacement = new QLabel("Срок размещения (мес.)", this);
  sPeriodOfPlacement = new QSpinBox(this);

  lInterestRate = new QLabel("Процентная ставка", this);
  dsInterestRate = new QDoubleSpinBox(this);

  lTaxRate = new QLabel("Налоговая ставка", this);
  dsTaxRate = new QDoubleSpinBox(this);

  lPerOfPay = new QLabel("Периодичность выплат", this);
  cmPerOfPay = new QComboBox(this);

  lStartDate = new QLabel("Начало срока (д.м.г.)", this);
  sbStartDateDay = new QSpinBox(this);
  sbStartDateMonth = new QSpinBox(this);
  sbStartDateYear = new QSpinBox(this);

  lCapital = new QLabel("Капитализация процентов", this);
  cbCapital = new QCheckBox(this);

  pbAddMoney = new QPushButton("Пополнения", this);
  pbRemMoney = new QPushButton("Снятия", this);
  pbCalc = new QPushButton("Рассчитать", this);

  fAddMoney = new QFrame(this);
  vblAddM = new QVBoxLayout(this);
  glAddM = new QGridLayout(this);
  pbPlusAddM = new QPushButton("+", this);
  pbMinusAddM = new QPushButton("-", this);
  //    cbAdd = new QComboBox(this);
  twAdd = new QTableWidget(this);
  pbCloseAdd = new QPushButton("Закрыть", this);

  fRemMoney = new QFrame(this);
  vblRemM = new QVBoxLayout(this);
  glRemM = new QGridLayout(this);
  pbPlusRemM = new QPushButton("+", this);
  pbMinusRemM = new QPushButton("-", this);
  twRem = new QTableWidget(this);
  pbCloseRem = new QPushButton("Закрыть", this);

  output = new QFrame(this);
  vblOut = new QVBoxLayout(this);
  sumInterest = new QLabel(this);
  sumEndTerm = new QLabel(this);
  sumTax = new QLabel(this);
  pbCloseOut = new QPushButton("Закрыть", this);
}

void DepositCalc::Properties() {
  setFixedSize(400, 400);

  glDep->setContentsMargins(10, 30, 10, 10);

  lDepAmount->setMinimumSize(150, 25);
  dsDepAmount->setMinimumSize(150, 25);
  dsDepAmount->setRange(0, 100000000);
  dsDepAmount->setValue(3500000);

  lPeriodOfPlacement->setMinimumSize(150, 25);
  sPeriodOfPlacement->setMinimumSize(150, 25);
  sPeriodOfPlacement->setRange(0, 99);
  sPeriodOfPlacement->setValue(9);

  lInterestRate->setMinimumSize(150, 25);
  dsInterestRate->setMinimumSize(150, 25);
  dsInterestRate->setRange(0, 100);
  dsInterestRate->setValue(8.0);

  lTaxRate->setMinimumSize(150, 25);
  dsTaxRate->setMinimumSize(150, 25);
  dsTaxRate->setRange(0, 100);
  dsTaxRate->setValue(13.0);

  lPerOfPay->setMinimumSize(150, 25);
  cmPerOfPay->setMinimumSize(150, 25);
  cmPerOfPay->addItem("Раз в месяц");
  cmPerOfPay->addItem("Раз в пол года");
  cmPerOfPay->addItem("Раз в год");
  cmPerOfPay->addItem("В конце срока");

  sbStartDateYear->setRange(1900, 2500);
  sbStartDateMonth->setRange(1, 12);
  sbStartDateYear->setValue(QDate::currentDate().year());
  sbStartDateMonth->setValue(QDate::currentDate().month());
  sbStartDateDay->setValue(QDate::currentDate().day());
  setStartDay();

  lCapital->setMinimumSize(150, 25);

  pbAddMoney->setFixedSize(100, 25);
  pbRemMoney->setFixedSize(100, 25);
  pbCalc->setFixedSize(100, 25);

  // Пополнения
  fAddMoney->setFixedSize(400, 400);
  vblAddM->setContentsMargins(10, 30, 10, 10);
  pbPlusAddM->setFixedSize(25, 25);
  pbMinusAddM->setFixedSize(25, 25);
  glAddM->setHorizontalSpacing(330);
  twAdd->setColumnCount(2);
  twAdd->setColumnWidth(0, 210);
  twAdd->setColumnWidth(1, 155);
  twAdd->setHorizontalHeaderLabels(QStringList() << "Периодичность пополнения"
                                                 << "Сумма");

  pbCloseAdd->setFixedSize(100, 25);

  // Снятия
  fRemMoney->setFixedSize(400, 400);
  vblRemM->setContentsMargins(10, 30, 10, 10);
  pbPlusRemM->setFixedSize(25, 25);
  pbMinusRemM->setFixedSize(25, 25);
  twRem->setColumnCount(2);
  glRemM->setHorizontalSpacing(330);
  twRem->setColumnWidth(0, 210);
  twRem->setColumnWidth(1, 155);
  twRem->setHorizontalHeaderLabels(QStringList() << "Периодичность снятия"
                                                 << "Сумма");
  pbCloseRem->setFixedSize(100, 25);

  output->setFixedSize(400, 400);

  sumInterest->setFixedSize(380, 25);
  sumEndTerm->setFixedSize(380, 25);
  sumTax->setFixedSize(380, 25);

  pbCloseOut->setFixedSize(100, 25);

  output->hide();
  fAddMoney->hide();
  fRemMoney->hide();

  // Список пополнений

  //    pbCloseAdd->setFixedSize(100, 25);

  // Список частичных снятий

  //    pbCloseRem->setFixedSize(100, 25);
}

void DepositCalc::setStartDay() {
  int date = 0;
  date = sbStartDateMonth->value() == 12 ? 0 : sbStartDateMonth->value();
  dateCorrect(&date, isLeap(sbStartDateYear->value()));
  sbStartDateDay->setRange(1, date);
}

void DepositCalc::Layouts() {
  setLayout(glDep);

  glDep->addWidget(lDepAmount, 0, 0, 1, 1);
  glDep->addWidget(dsDepAmount, 0, 1, 1, 3);

  glDep->addWidget(lPeriodOfPlacement, 1, 0, 1, 1);
  glDep->addWidget(sPeriodOfPlacement, 1, 1, 1, 3);

  glDep->addWidget(lInterestRate, 2, 0, 1, 1);
  glDep->addWidget(dsInterestRate, 2, 1, 1, 3);

  glDep->addWidget(lTaxRate, 3, 0, 1, 1);
  glDep->addWidget(dsTaxRate, 3, 1, 1, 3);

  glDep->addWidget(lPerOfPay, 4, 0, 1, 1);
  glDep->addWidget(cmPerOfPay, 4, 1, 1, 3);

  glDep->addWidget(lStartDate, 5, 0, 1, 1);
  glDep->addWidget(sbStartDateDay, 5, 1, 1, 1);
  glDep->addWidget(sbStartDateMonth, 5, 2, 1, 1);
  glDep->addWidget(sbStartDateYear, 5, 3, 1, 1);

  glDep->addWidget(lCapital, 6, 0, 1, 1);
  glDep->addWidget(cbCapital, 6, 1, 1, 1);

  glDep->addWidget(pbAddMoney, 7, 0, 1, 1);
  glDep->addWidget(pbRemMoney, 8, 0, 1, 1);

  glDep->addWidget(pbCalc, 9, 0, 1, 1);

  fAddMoney->setLayout(vblAddM);
  vblAddM->addLayout(glAddM);
  glAddM->addWidget(pbPlusAddM, 0, 0, 1, 1);
  glAddM->addWidget(pbMinusAddM, 0, 1, 1, 1);
  vblAddM->addWidget(twAdd);
  vblAddM->addWidget(pbCloseAdd);

  fRemMoney->setLayout(vblRemM);
  vblRemM->addLayout(glRemM);
  glRemM->addWidget(pbPlusRemM, 0, 0, 1, 1);
  glRemM->addWidget(pbMinusRemM, 0, 1, 1, 1);
  vblRemM->addWidget(twRem);
  vblRemM->addWidget(pbCloseRem);

  output->setLayout(vblOut);
  vblOut->addWidget(sumInterest);
  vblOut->addWidget(sumEndTerm);
  vblOut->addWidget(sumTax);
  vblOut->addWidget(pbCloseOut);
}

void DepositCalc::Connector() {
  connect(pbCalc, SIGNAL(clicked()), this, SLOT(slotCalc()));
  connect(pbCloseOut, SIGNAL(clicked()), this, SLOT(slotCloseOut()));

  connect(pbAddMoney, SIGNAL(clicked()), this, SLOT(slotAddM()));
  connect(pbRemMoney, SIGNAL(clicked()), this, SLOT(slotRemM()));

  connect(pbCloseAdd, SIGNAL(clicked()), this, SLOT(slotCloseAdd()));
  connect(pbCloseRem, SIGNAL(clicked()), this, SLOT(slotCloseRem()));

  connect(pbPlusAddM, SIGNAL(clicked()), this, SLOT(slotPlusAdd()));
  connect(pbMinusAddM, SIGNAL(clicked()), this, SLOT(slotMinusAdd()));

  connect(pbPlusRemM, SIGNAL(clicked()), this, SLOT(slotPlusRem()));
  connect(pbMinusRemM, SIGNAL(clicked()), this, SLOT(slotMinusRem()));

  connect(sbStartDateYear, SIGNAL(valueChanged(int)), this,
          SLOT(setStartDay()));
  connect(sbStartDateMonth, SIGNAL(valueChanged(int)), this,
          SLOT(setStartDay()));
}

void DepositCalc::slotAddM() { fAddMoney->show(); }

void DepositCalc::slotRemM() { fRemMoney->show(); }

void DepositCalc::slotCloseAdd() { fAddMoney->hide(); }

void DepositCalc::slotCloseRem() { fRemMoney->hide(); }

void DepositCalc::slotCalc() {
  Deposit dp;

  dp.depositAmount = dsDepAmount->value();
  dp.periodOfPlacement = (double)sPeriodOfPlacement->value();
  dp.interestRate = dsInterestRate->value();
  dp.taxRate = dsTaxRate->value();
  dp.paymentsType = cmPerOfPay->currentIndex();
  dp.interestCapitalization = cbCapital->isChecked() ? 1 : 0;
  dp.currentMoth = sbStartDateMonth->value();
  dp.currentYear = sbStartDateYear->value();
  dp.currentDay = sbStartDateDay->value();

  dp.addCount = twAdd->rowCount();
  for (int i = 0; i < twAdd->rowCount(); i++) {
    dp.replenishmentList[i].term =
        qobject_cast<QComboBox *>(twAdd->cellWidget(i, 0))->currentIndex();
    dp.replenishmentList[i].money =
        qobject_cast<QDoubleSpinBox *>(twAdd->cellWidget(i, 1))->value();
  }
  dp.remCount = twRem->rowCount();
  for (int i = 0; i < twRem->rowCount(); i++) {
    dp.listPartialWithdrawals[i].term =
        qobject_cast<QComboBox *>(twRem->cellWidget(i, 0))->currentIndex();
    dp.listPartialWithdrawals[i].money =
        qobject_cast<QDoubleSpinBox *>(twRem->cellWidget(i, 1))->value();
  }

  depositCalcCore(&dp);

  sumInterest->setText("Начисленные проценты: " +
                       QString::number(dp.sumInterest, 'f', 2));
  sumEndTerm->setText("Сумма на вкладе к концу срока: " +
                      QString::number(dp.sumEndTerm, 'f', 2));
  sumTax->setText("Cумма налога: " + QString::number(dp.sumTax, 'f', 2));

  output->show();
}

void DepositCalc::slotCloseOut() { output->hide(); }

void DepositCalc::slotPlusAdd() {
  int row = twAdd->rowCount();
  if (row < 255) {
    QComboBox *cmb = new QComboBox(this);
    QDoubleSpinBox *dsb = new QDoubleSpinBox(this);
    cmb->addItems(QStringList() << "Раз в месяц"
                                << "Раз в пол года"
                                << "Раз в год");
    dsb->setRange(0, 100000000);
    twAdd->insertRow(row);
    twAdd->setCellWidget(row, 0, cmb);
    twAdd->setCellWidget(row, 1, dsb);
  }
  qDebug() << "plusAdd";
}

void DepositCalc::slotMinusAdd() {
  int row = twAdd->rowCount();
  if (row > 0) twAdd->removeRow(row - 1);
  qDebug() << "minusAdd";
}

void DepositCalc::slotPlusRem() {
  int row = twRem->rowCount();
  if (row < 255) {
    QComboBox *cmb = new QComboBox(this);
    QDoubleSpinBox *dsb = new QDoubleSpinBox(this);
    cmb->addItems(QStringList() << "Раз в месяц"
                                << "Раз в пол года"
                                << "Раз в год");
    dsb->setRange(0, 100000000);
    twRem->insertRow(row);
    twRem->setCellWidget(row, 0, cmb);
    twRem->setCellWidget(row, 1, dsb);
  }
  qDebug() << "plusRem";
}

void DepositCalc::slotMinusRem() {
  int row = twRem->rowCount();
  if (row > 0) twRem->removeRow(row - 1);
  qDebug() << "minusRem";
}
