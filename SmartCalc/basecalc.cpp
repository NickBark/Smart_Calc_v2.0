#include "basecalc.h"

BaseCalc::BaseCalc(QFrame* parent) : QFrame{parent} {
    graph = new Graph();
    cg = new CustomGraph();

    pointArr = new Point[POINT_NUM];
    yNewArr = new double[POINT_NUM];

    scale = 5;

    graph->bc = this;

    wasX = 0;

    Designer();
    Properties();
    Layouts();
    Connector();
}

BaseCalc::~BaseCalc() {
    delete graph;
    delete cg;
}

void BaseCalc::Designer() {
    vblCalc = new QVBoxLayout(this);
    leResultText = new QLabel(this);
    leText = new QLineEdit(this);

    glCalc = new QGridLayout(this);

    pb0 = new QPushButton("0", this);
    pb1 = new QPushButton("1", this);
    pb2 = new QPushButton("2", this);
    pb3 = new QPushButton("3", this);
    pb4 = new QPushButton("4", this);
    pb5 = new QPushButton("5", this);
    pb6 = new QPushButton("6", this);
    pb7 = new QPushButton("7", this);
    pb8 = new QPushButton("8", this);
    pb9 = new QPushButton("9", this);
    pbAdd = new QPushButton("+", this);
    pbSub = new QPushButton("-", this);
    pbMul = new QPushButton("*", this);
    pbDiv = new QPushButton("/", this);
    pbMod = new QPushButton("%", this);
    pbPow = new QPushButton("^", this);

    pbSin = new QPushButton("sin", this);
    pbCos = new QPushButton("cos", this);
    pbAsin = new QPushButton("asin", this);
    pbAcos = new QPushButton("acos", this);
    pbTan = new QPushButton("tan", this);
    pbAtan = new QPushButton("atan", this);
    pbLn = new QPushButton("ln", this);
    pbLog10 = new QPushButton("log", this);
    pbSqrt = new QPushButton("sqrt", this);
    //    leScale = new QLineEdit(this);

    pbClear = new QPushButton("clear", this);
    pbBack = new QPushButton("<==", this);

    pbX = new QPushButton("x", this);
    hblRange = new QHBoxLayout(this);
    spbXmin = new QSpinBox(this);
    spbXmax = new QSpinBox(this);

    pbResult = new QPushButton("=", this);
}

void BaseCalc::Properties() {
    setFixedSize(400, 400);
    setWindowTitle("Graphing Calc");

    graph->setWindowTitle("Graph");

    graph->setFixedSize(WIDTH, HEIGHT);

    pb0->setFixedSize(60, 25);
    pb1->setFixedSize(60, 25);
    pb2->setFixedSize(60, 25);
    pb3->setFixedSize(60, 25);
    pb4->setFixedSize(60, 25);
    pb5->setFixedSize(60, 25);
    pb6->setFixedSize(60, 25);
    pb7->setFixedSize(60, 25);
    pb8->setFixedSize(60, 25);
    pb9->setFixedSize(60, 25);
    pbAdd->setFixedSize(60, 25);
    pbSub->setFixedSize(60, 25);
    pbMul->setFixedSize(60, 25);
    pbDiv->setFixedSize(60, 25);
    pbMod->setFixedSize(60, 25);
    pbPow->setFixedSize(60, 25);
    pbResult->setFixedSize(60, 25);

    pbSin->setFixedSize(60, 25);
    pbCos->setFixedSize(60, 25);
    pbAsin->setFixedSize(60, 25);
    pbAcos->setFixedSize(60, 25);
    pbTan->setFixedSize(60, 25);
    pbAtan->setFixedSize(60, 25);
    pbLn->setFixedSize(60, 25);
    pbLog10->setFixedSize(60, 25);
    pbSqrt->setFixedSize(60, 25);

    pbBack->setFixedSize(60, 25);
    pbClear->setFixedSize(60, 25);

    //    leScale->setFixedSize(60, 25);
    //    leScale->setPlaceholderText("Scale=5");

    spbXmin->setFixedSize(120, 25);
    spbXmax->setFixedSize(120, 25);
    spbXmin->setPrefix("Xmin=");
    spbXmax->setPrefix("Xmax=");

    spbXmin->setRange(-1000000, 0);
    spbXmax->setRange(0, 1000000);

    spbXmin->setValue(-100);
    spbXmax->setValue(100);

    pbX->setFixedSize(60, 25);
}

void BaseCalc::Layouts() {
    int rowSpan = 1;
    int columnSpan = 1;

    setLayout(vblCalc);
    vblCalc->addWidget(leResultText);
    vblCalc->addWidget(leText);
    vblCalc->addLayout(glCalc);

    glCalc->addWidget(pb1, 0, 1, rowSpan, columnSpan);
    glCalc->addWidget(pb2, 0, 2, rowSpan, columnSpan);
    glCalc->addWidget(pb3, 0, 3, rowSpan, columnSpan);

    glCalc->addWidget(pb4, 1, 1, rowSpan, columnSpan);
    glCalc->addWidget(pb5, 1, 2, rowSpan, columnSpan);
    glCalc->addWidget(pb6, 1, 3, rowSpan, columnSpan);

    glCalc->addWidget(pb7, 2, 1, rowSpan, columnSpan);
    glCalc->addWidget(pb8, 2, 2, rowSpan, columnSpan);
    glCalc->addWidget(pb9, 2, 3, rowSpan, columnSpan);

    glCalc->addWidget(pb0, 3, 2, rowSpan, columnSpan);

    glCalc->addWidget(pbAdd, 4, 1, rowSpan, columnSpan);
    glCalc->addWidget(pbSub, 4, 2, rowSpan, columnSpan);
    glCalc->addWidget(pbMul, 4, 3, rowSpan, columnSpan);

    glCalc->addWidget(pbDiv, 5, 1, rowSpan, columnSpan);
    glCalc->addWidget(pbMod, 5, 2, rowSpan, columnSpan);
    glCalc->addWidget(pbPow, 5, 3, rowSpan, columnSpan);

    glCalc->addWidget(pbSin, 6, 1, rowSpan, columnSpan);
    glCalc->addWidget(pbCos, 6, 2, rowSpan, columnSpan);
    glCalc->addWidget(pbTan, 6, 3, rowSpan, columnSpan);

    glCalc->addWidget(pbAsin, 7, 1, rowSpan, columnSpan);
    glCalc->addWidget(pbAcos, 7, 2, rowSpan, columnSpan);
    glCalc->addWidget(pbAtan, 7, 3, rowSpan, columnSpan);

    glCalc->addWidget(pbLn, 8, 1, rowSpan, columnSpan);
    glCalc->addWidget(pbLog10, 8, 2, rowSpan, columnSpan);
    glCalc->addWidget(pbX, 8, 3, rowSpan, columnSpan);

    glCalc->addWidget(pbSqrt, 9, 1, rowSpan, columnSpan);
    glCalc->addWidget(pbBack, 9, 2, rowSpan, columnSpan);
    glCalc->addWidget(pbClear, 9, 3, rowSpan, columnSpan);

    glCalc->addWidget(pbResult, 10, 3, rowSpan, columnSpan);

    vblCalc->addLayout(hblRange);
    hblRange->addWidget(spbXmin);
    hblRange->addWidget(spbXmax);
}

void BaseCalc::Connector() {
    connect(pb0, SIGNAL(clicked()), this, SLOT(slotPb0()));
    connect(pb1, SIGNAL(clicked()), this, SLOT(slotPb1()));
    connect(pb2, SIGNAL(clicked()), this, SLOT(slotPb2()));
    connect(pb3, SIGNAL(clicked()), this, SLOT(slotPb3()));
    connect(pb4, SIGNAL(clicked()), this, SLOT(slotPb4()));
    connect(pb5, SIGNAL(clicked()), this, SLOT(slotPb5()));
    connect(pb6, SIGNAL(clicked()), this, SLOT(slotPb6()));
    connect(pb7, SIGNAL(clicked()), this, SLOT(slotPb7()));
    connect(pb8, SIGNAL(clicked()), this, SLOT(slotPb8()));
    connect(pb9, SIGNAL(clicked()), this, SLOT(slotPb9()));

    connect(pbAdd, SIGNAL(clicked()), this, SLOT(slotPbAdd()));
    connect(pbSub, SIGNAL(clicked()), this, SLOT(slotPbSub()));
    connect(pbMul, SIGNAL(clicked()), this, SLOT(slotPbMul()));
    connect(pbDiv, SIGNAL(clicked()), this, SLOT(slotPbDiv()));
    connect(pbMod, SIGNAL(clicked()), this, SLOT(slotPbMod()));
    connect(pbPow, SIGNAL(clicked()), this, SLOT(slotPbPow()));

    connect(pbSin, SIGNAL(clicked()), this, SLOT(slotPbSin()));
    connect(pbCos, SIGNAL(clicked()), this, SLOT(slotPbCos()));
    connect(pbAsin, SIGNAL(clicked()), this, SLOT(slotPbAsin()));
    connect(pbAcos, SIGNAL(clicked()), this, SLOT(slotPbAcos()));
    connect(pbTan, SIGNAL(clicked()), this, SLOT(slotPbTan()));
    connect(pbAtan, SIGNAL(clicked()), this, SLOT(slotPbAtan()));
    connect(pbLog10, SIGNAL(clicked()), this, SLOT(slotPbLog10()));
    connect(pbLn, SIGNAL(clicked()), this, SLOT(slotPbLn()));
    connect(pbSqrt, SIGNAL(clicked()), this, SLOT(slotPbSqrt()));

    connect(pbClear, SIGNAL(clicked()), this, SLOT(slotPbClear()));
    connect(pbBack, SIGNAL(clicked()), this, SLOT(slotPbBack()));

    connect(pbX, SIGNAL(clicked()), this, SLOT(slotPbX()));

    connect(pbResult, SIGNAL(clicked()), this, SLOT(slotPbResult()));
}

void BaseCalc::slotPbClear() {
    if (!leText->text().isEmpty()) qBackStr = leText->text();
    leText->setText("");
}

void BaseCalc::slotPbBack() { leText->setText(qBackStr); }

void BaseCalc::slotPbSqrt() {
    qStr = leText->text();
    qStr += "sqrt(";
    leText->setText(qStr);
}

void BaseCalc::slotPb0() {
    qStr = leText->text();
    qStr += "0";
    leText->setText(qStr);
}
void BaseCalc::slotPb1() {
    qStr = leText->text();
    qStr += "1";
    leText->setText(qStr);
}
void BaseCalc::slotPb2() {
    qStr = leText->text();
    qStr += "2";
    leText->setText(qStr);
}
void BaseCalc::slotPb3() {
    qStr = leText->text();
    qStr += "3";
    leText->setText(qStr);
}
void BaseCalc::slotPb4() {
    qStr = leText->text();
    qStr += "4";
    leText->setText(qStr);
}
void BaseCalc::slotPb5() {
    qStr = leText->text();
    qStr += "5";
    leText->setText(qStr);
}
void BaseCalc::slotPb6() {
    qStr = leText->text();
    qStr += "6";
    leText->setText(qStr);
}
void BaseCalc::slotPb7() {
    qStr = leText->text();
    qStr += "7";
    leText->setText(qStr);
}
void BaseCalc::slotPb8() {
    qStr = leText->text();
    qStr += "8";
    leText->setText(qStr);
}
void BaseCalc::slotPb9() {
    qStr = leText->text();
    qStr += "9";
    leText->setText(qStr);
}

void BaseCalc::slotPbAdd() {
    qStr = leText->text();
    qStr += "+";
    leText->setText(qStr);
}

void BaseCalc::slotPbSub() {
    qStr = leText->text();
    qStr += "-";
    leText->setText(qStr);
}

void BaseCalc::slotPbMul() {
    qStr = leText->text();
    qStr += "*";
    leText->setText(qStr);
}

void BaseCalc::slotPbDiv() {
    qStr = leText->text();
    qStr += "/";
    leText->setText(qStr);
}

void BaseCalc::slotPbMod() {
    qStr = leText->text();
    qStr += "%";
    leText->setText(qStr);
}

void BaseCalc::slotPbPow() {
    qStr = leText->text();
    qStr += "^";
    leText->setText(qStr);
}

void BaseCalc::slotPbSin() {
    qStr = leText->text();
    qStr += "sin(";
    leText->setText(qStr);
}

void BaseCalc::slotPbCos() {
    qStr = leText->text();
    qStr += "cos(";
    leText->setText(qStr);
}

void BaseCalc::slotPbAsin() {
    qStr = leText->text();
    qStr += "asin(";
    leText->setText(qStr);
}

void BaseCalc::slotPbAcos() {
    qStr = leText->text();
    qStr += "acos(";
    leText->setText(qStr);
}

void BaseCalc::slotPbTan() {
    qStr = leText->text();
    qStr += "tan(";
    leText->setText(qStr);
}

void BaseCalc::slotPbAtan() {
    qStr = leText->text();
    qStr += "atan(";
    leText->setText(qStr);
}

void BaseCalc::slotPbLn() {
    qStr = leText->text();
    qStr += "ln(";
    leText->setText(qStr);
}

void BaseCalc::slotPbLog10() {
    qStr = leText->text();
    qStr += "log(";
    leText->setText(qStr);
}

void BaseCalc::slotPbX() {
    qStr = leText->text();
    qStr += "x";
    leText->setText(qStr);
}

void BaseCalc::slotPbResult() {
    //    QString scaleStr;
    qStr = leText->text();
    qBackStr = qStr;
    qStr.replace(QRegExp("\\."), ",");

    //    if (!leScale->text().isEmpty()) {
    //        scaleStr = leScale->text();
    //        scaleStr.replace(QRegExp(","), ".");
    //        scale = scaleStr.toDouble();
    //    }

    xMin = spbXmin->value();
    xMax = spbXmax->value();

    if (qStr.contains("x", Qt::CaseInsensitive)) wasX = 1;
    if (qStr.size()) {
        Priority pr = {};

        double result = 0;
        char resStr[255] = {};

        QByteArray br = qStr.toLatin1();
        const char* inputStr = br.data();

        initPriority(&pr);
        if (shuntingYard(inputStr, resStr, &pr)) {
            qDebug() << "ERROR";
            QMessageBox::warning(this, "ERROR", "ERROR");
            free(pr.priority);
            return;
        }
        qDebug() << resStr;

        if (wasX) {
            //            int wasNan = 0;
            double x = xMin;
            double h = 0.01;
            num = fabs(xMax - xMin);
            //            xMin = 180 * xMin / S21_PI;
            //            xMax = 180 * xMax / S21_PI;
            //            pointNum = abs(xMax - xMin);
            //            Mx = pointNum / (WIDTH - 1);
            //            yMin = 0.;
            //            yMax = 0.;

            //            for (int i = 0; i < num; i++, x += S21_PI / 180) {
            //                ret = calcus(resStr, &pr, x, &result);

            //                if (yMin >= result) yMin = result;
            //                if (yMax <= result) yMax = result;
            //                if (ret) {
            //                    graph->skip = 1;
            //                    pointArr[i].error = 1;
            //                    continue;
            //                } else {
            //                    pointArr[i].x = x;
            //                    pointArr[i].y = result;
            //                    pointArr[i].error = 0;
            //                }
            //                //            }
            //            }

            //            int wasDown = 0;
            //            if (num > 50000) h = 1;

            //            double count = -100.;
            //            for (; count < 100.; count += S21_PI / 180) {
            //                cg->x.push_back(count);
            //                cg->y.push_back(1 / count);
            //            }
            cg->x.clear();
            cg->y.clear();
            cg->x2.clear();
            cg->y2.clear();

            if (fabs(xMax - xMin) > 1000.) h = 1;
            if (fabs(xMax - xMin) > 100000.) h = 10;

            for (int i = 0; x <= xMax; i++, x += h) {
                calcY(resStr, &pr, x, &result);
            }
            calcY(resStr, &pr, xMax, &result);
            //            ret = calcus(resStr, &pr, xMax, &result);

            //            if (ret) {
            //                wasNan = 1;
            //            } else {
            //                if (!wasNan) {
            //                    cg->x.push_back(xMax);
            //                    cg->y.push_back(result);
            //                } else {
            //                    cg->x2.push_back(xMax);
            //                    cg->y2.push_back(result);
            //                }
            //            }

            if (wasX) {
                cg->drawGraph();
                cg->show();
            }
            qDebug() << "FIN";

            //            convertToWindow();
            //            if (wasX) graph->show();
            wasX = 0;
        } else if (calcus(resStr, &pr, 1, &result)) {
            qDebug() << "ERROR CALCUS";
            QMessageBox::warning(this, "ERROR", "ERROR");
        } else {
            qStr = QString::number(result, 'g', 10);
            leText->setText(qStr);
        }

        free(pr.priority);
    } else {
        qDebug() << "empty str";
    }
}

void BaseCalc::calcY(char* resStr, Priority* pr, double x, double* y) {
    int ret = 0;

    ret = calcus(resStr, pr, x, y);

    if (ret) {
        cg->x.push_back(x);
        cg->y.push_back(std::numeric_limits<double>::quiet_NaN());
    } else {
        cg->x.push_back(x);
        cg->y.push_back(*y);
    }
}

void BaseCalc::convertToWindow() {
    dy = abs(yMin - yMax) / HEIGHT;

    yNewArr[0] = yMin;

    for (int i = 1; i < num; i++) {
        yNewArr[i] = yNewArr[i - 1] + dy;
    }

    yNewArr[num - 1] = yMax;

    //    My = (HEIGHT - 1) / abs(yMax - yMin);

    //    graph->image = QImage();

    //    graph->image.fill(Qt::black);
    //    for (int i = 0; i < num; i++) {
    //        if (pointArr[i].error == 1) continue;
    //        pointArr[i].ix = round(i / Mx);
    //        pointArr[i].jy = HEIGHT - round(My * pointArr[i].y + HEIGHT / 2);

    //        //        graph->image.setPixel(pointArr[i].ix, pointArr[i].jy,
    //        //        qRgb(255, 0, 0));
    //    }
}
