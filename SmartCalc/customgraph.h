#ifndef CUSTOMGRAPH_H
#define CUSTOMGRAPH_H

#include "dependencies.hpp"

class CustomGraph : public QCustomPlot {
    Q_OBJECT
   public:
    explicit CustomGraph(QCustomPlot* parent = nullptr);

    QVector<double> x;
    QVector<double> y;

    QVector<double> x2;
    QVector<double> y2;

    void drawGraph();

   signals:
};

#endif  // CUSTOMGRAPH_H
