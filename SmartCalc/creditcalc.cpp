#include "creditcalc.h"

CreditCalc::CreditCalc(QFrame* parent) : QFrame{parent} {
  Designer();
  Properties();
  Layouts();
  Connector();
}

void CreditCalc::Designer() {
  glButtons = new QGridLayout(this);
  pbResult = new QPushButton("Посчитать", this);
  cmType = new QComboBox(this);
  dsbSum = new QDoubleSpinBox(this);

  lTime = new QLabel("Срок кредита (мес.)", this);
  lPersent = new QLabel("Процентная ставка", this);
  sbTime = new QSpinBox(this);
  dsbPersent = new QDoubleSpinBox(this);
  lSum = new QLabel("Cумма кредита", this);

  lStartDate = new QLabel("Начало срока (д.м.г.)", this);
  sbStartDateDay = new QSpinBox(this);
  sbStartDateMonth = new QSpinBox(this);
  sbStartDateYear = new QSpinBox(this);

  outputAnn = new QFrame(this);
  glOutAnn = new QGridLayout(this);
  lMonthlyPayment = new QLabel(this);
  lOverpayment = new QLabel(this);
  lTotalPayment = new QLabel(this);
  pbCloseAnn = new QPushButton("Закрыть", this);

  outputDiff = new QFrame(this);
  hblOutDiff = new QVBoxLayout(this);
  glOutDiff = new QGridLayout(this);
  lOverpaymentDiff = new QLabel(this);
  lTotalPaymentDiff = new QLabel(this);
  pbCloseDiff = new QPushButton("Закрыть", this);
  saDiff = new QScrollArea(this);

  lMonthlyPaymentDiff = new QLabel(this);
}

void CreditCalc::Properties() {
  this->setFixedSize(400, 400);
  pbResult->setFixedSize(100, 40);
  //    cmType->setFixedSize(200, 40);
  //    dsbSum->setFixedSize(200, 40);
  dsbSum->setMaximumSize(200, 25);
  dsbSum->setRange(0, 1000000000);

  sbTime->setMaximumSize(70, 25);
  dsbPersent->setMaximumSize(70, 25);

  lTime->setMinimumSize(200, 25);
  lPersent->setMinimumSize(200, 25);

  cmType->addItem("аннуитетный тип ежемесячных платежей");
  cmType->addItem("дифференцированный тип ежемесячных платежей");

  sbStartDateYear->setRange(1900, 2500);
  sbStartDateMonth->setRange(1, 12);
  sbStartDateYear->setValue(QDate::currentDate().year());
  sbStartDateMonth->setValue(QDate::currentDate().month());
  sbStartDateDay->setValue(QDate::currentDate().day());
  setStartDay();

  outputAnn->setFixedSize(400, 400);

  lMonthlyPayment->setMaximumSize(400, 40);
  lOverpayment->setMaximumSize(400, 40);
  lTotalPayment->setMaximumSize(400, 40);
  pbCloseAnn->setFixedSize(60, 40);

  saDiff->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  saDiff->setWidgetResizable(true);
  saDiff->setGeometry(0, 25, 400, 380);

  //    lMonthlyPaymentDiff->setMaximumHeight(40);
  lOverpaymentDiff->setMaximumSize(400, 40);
  lTotalPaymentDiff->setMaximumSize(400, 40);
  pbCloseDiff->setFixedSize(60, 40);

  outputAnn->hide();
  saDiff->hide();
}

void CreditCalc::Layouts() {
  this->setLayout(glButtons);

  glButtons->addWidget(cmType, 0, 0, 1, 4);
  glButtons->addWidget(lSum, 2, 0, 1, 1);
  glButtons->addWidget(dsbSum, 2, 1, 1, 3);
  glButtons->addWidget(lTime, 3, 0, 1, 1);
  glButtons->addWidget(sbTime, 3, 1, 1, 3);
  glButtons->addWidget(lPersent, 4, 0, 1, 1);
  glButtons->addWidget(dsbPersent, 4, 1, 1, 3);

  glButtons->addWidget(lStartDate, 5, 0, 1, 1);
  glButtons->addWidget(sbStartDateDay, 5, 1, 1, 1);
  glButtons->addWidget(sbStartDateMonth, 5, 2, 1, 1);
  glButtons->addWidget(sbStartDateYear, 5, 3, 1, 1);

  glButtons->addWidget(pbResult, 6, 0, 1, 1);

  outputAnn->setLayout(glOutAnn);
  glOutAnn->addWidget(lMonthlyPayment, 0, 0, 1, 2);
  glOutAnn->addWidget(lOverpayment, 1, 0, 1, 2);
  glOutAnn->addWidget(lTotalPayment, 2, 0, 1, 2);
  glOutAnn->addWidget(pbCloseAnn, 3, 1, 1, 1);

  saDiff->setWidget(outputDiff);
  outputDiff->setLayout(glOutDiff);
  //    glOutDiff->addLayout(hblOutDiff, 1, 0, 1, 2);
  glOutDiff->addWidget(lMonthlyPaymentDiff, 1, 0, 1, 2);
  glOutDiff->addWidget(lOverpaymentDiff, 2, 0, 1, 2);
  glOutDiff->addWidget(lTotalPaymentDiff, 3, 0, 1, 2);
  glOutDiff->addWidget(pbCloseDiff, 4, 1, 1, 1);
}

void CreditCalc::Connector() {
  connect(pbResult, SIGNAL(clicked()), this, SLOT(slotPbResult()));
  connect(pbCloseAnn, SIGNAL(clicked()), this, SLOT(slotPbCloseAnn()));
  connect(pbCloseDiff, SIGNAL(clicked()), this, SLOT(slotPbCloseDiff()));

  connect(sbStartDateYear, SIGNAL(valueChanged(int)), this,
          SLOT(setStartDay()));
  connect(sbStartDateMonth, SIGNAL(valueChanged(int)), this,
          SLOT(setStartDay()));
}

void CreditCalc::setStartDay() {
  int date = 0;
  date = sbStartDateMonth->value() == 12 ? 0 : sbStartDateMonth->value();
  dateCorrect(&date, isLeap(sbStartDateYear->value()));
  sbStartDateDay->setRange(1, date);
}

void CreditCalc::slotPbCloseAnn() { outputAnn->hide(); }

void CreditCalc::slotPbCloseDiff() { saDiff->hide(); }

void CreditCalc::slotPbResult() {
  cr.type = cmType->currentIndex();
  cr.interestRate = dsbPersent->value();
  cr.totalCredit = dsbSum->value();
  cr.term = sbTime->value();
  cr.mainMonthSum = cr.totalCredit / cr.term;
  cr.totalPayment = 0.;
  cr.overpaymentOnCredit = 0.;
  cr.monthlyPayment = 0.;

  if (cr.type == 0) {
    creditCalcCore(&cr);
    lMonthlyPayment->setText("Ежемесячный платеж: " +
                             QString::number(cr.monthlyPayment, 'f', 2));
    lOverpayment->setText("Переплата по кредиту: " +
                          QString::number(cr.overpaymentOnCredit, 'f', 2));
    lTotalPayment->setText("Общая выплата: " +
                           QString::number(cr.totalPayment, 'f', 2));
    outputAnn->show();
  } else if (cr.type == 1) {
    qDebug() << "mainMonthSum: " << cr.mainMonthSum;
    QString strMonth = NULL;
    int dateTmp = sbStartDateMonth->value();
    int currYear = sbStartDateYear->value();
    cr.days = sbStartDateDay->value();

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

      strMonth += QString::number(currYear + (dateTmp - 1 + i) / 12);
      strMonth += " ";
      dateToString(cr.date, &strMonth);
      strMonth += ": ";
      creditCalcCore(&cr);
      strMonth += QString::number(cr.monthlyPayment, 'f', 2);
      strMonth += "\n";
      lMonthlyPaymentDiff->setText(strMonth);
    }

    lOverpaymentDiff->setText("Переплата по кредиту: " +
                              QString::number(cr.overpaymentOnCredit, 'f', 2));
    lTotalPaymentDiff->setText("Общая выплата: " +
                               QString::number(cr.totalPayment, 'f', 2));

    saDiff->show();
  }
}

void CreditCalc::dateToString(int date, QString* strDate) {
  if (date == JANUARY)
    *strDate += "JANUARY";
  else if (date == FEBRUARY)
    *strDate += "FEBRUARY";
  else if (date == MARCH)
    *strDate += "MARCH";
  else if (date == APRIL)
    *strDate += "APRIL";
  else if (date == MAY)
    *strDate += "MAY";
  else if (date == JUNE)
    *strDate += "JUNE";
  else if (date == JULY)
    *strDate += "JULY";
  else if (date == AUGUST)
    *strDate += "AUGUST";
  else if (date == SEPTEMBER)
    *strDate += "SEPTEMBER";
  else if (date == OCTOBER)
    *strDate += "OCTOBER";
  else if (date == NOVEMBER)
    *strDate += "NOVEMBER";
  else if (date == DECEMBER)
    *strDate += "DECEMBER";
}
