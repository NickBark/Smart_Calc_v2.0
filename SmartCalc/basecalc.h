#ifndef BASECALC_H
#define BASECALC_H

#include "customgraph.h"
#include "dependencies.hpp"
#include "graph.hpp"

class BaseCalc : public QFrame {
  Q_OBJECT
 public:
  explicit BaseCalc(QFrame* parent = nullptr);
  ~BaseCalc();

  int num;

  int wasX;
  Point* pointArr;
  double pointNum;
  double xMin;
  double xMax;
  double yMin;
  double yMax;
  double dx;
  double dy;

  double Mx;  // масштаб по X
  double My;  // масштаб по Y

  int scale;  // масштаб

  // массив для отрисовки шкалы значений
  double* yAxis;
  double* xAxis;
  double* yNewArr;
  int yNewArrNum;

  int numbOfPoint;
  void convertToWindow();
  void initGraph();
  void calcY(char* resStr, Priority* pr, double x,
             double* y);  // одна итерация цикла

  void diyGraph(char* resStr, Priority* pr, double* result);

  void Designer();
  void Properties();
  void Layouts();
  void Connector();

  Graph* graph;
  CustomGraph* cg;

  QVBoxLayout* vblCalc;
  QLabel* leResultText;
  QLineEdit* leText;  //  поле ввода

  QGridLayout* glCalc;
  // layout glCalc
  QPushButton* pb0;
  QPushButton* pb1;
  QPushButton* pb2;
  QPushButton* pb3;
  QPushButton* pb4;
  QPushButton* pb5;
  QPushButton* pb6;
  QPushButton* pb7;
  QPushButton* pb8;
  QPushButton* pb9;
  QPushButton* pbAdd;
  QPushButton* pbSub;
  QPushButton* pbMul;
  QPushButton* pbDiv;
  QPushButton* pbMod;
  QPushButton* pbPow;
  QPushButton* pbResult;
  QPushButton* pbSin;
  QPushButton* pbCos;
  QPushButton* pbAsin;
  QPushButton* pbAcos;
  QPushButton* pbTan;
  QPushButton* pbAtan;
  QPushButton* pbLn;
  QPushButton* pbLog10;
  QPushButton* pbSqrt;
  QPushButton* pbX;
  QPushButton* pbClear;
  QPushButton* pbBack;
  //    QLineEdit* leScale;

  QHBoxLayout* hblRange;
  QSpinBox* spbXmin;
  QSpinBox* spbXmax;
  // layout glCalc

  QString qStr;      // содержит данные из поля ввода
  QString qBackStr;  // запомнить строку

 private slots:
  void slotPb0();
  void slotPb1();
  void slotPb2();
  void slotPb3();
  void slotPb4();
  void slotPb5();
  void slotPb6();
  void slotPb7();
  void slotPb8();
  void slotPb9();
  void slotPbAdd();
  void slotPbSub();
  void slotPbMul();
  void slotPbDiv();
  void slotPbMod();
  void slotPbPow();
  void slotPbSin();
  void slotPbCos();
  void slotPbAsin();
  void slotPbAcos();
  void slotPbTan();
  void slotPbAtan();
  void slotPbLn();
  void slotPbLog10();
  void slotPbSqrt();
  void slotPbResult();
  void slotPbX();

  void slotPbClear();
  void slotPbBack();

  //    void slotMenuBase();
  //    void slotMenuCredit();
  //    void slotMenuDeposit();
};

#endif  // BASECALC_H
