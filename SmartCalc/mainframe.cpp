#include "mainframe.h"

MainFrame::MainFrame(QFrame *parent) : QFrame{parent} {
  baseCalc = new BaseCalc(this);
  creditCalc = new CreditCalc(this);
  depositCalc = new DepositCalc(this);

  setFixedSize(400, 400);
}
