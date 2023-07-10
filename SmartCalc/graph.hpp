#ifndef GRAPH_H
#define GRAPH_H

#include "dependencies.hpp"

class BaseCalc;

class Graph : public QFrame {
    Q_OBJECT

   public:
    explicit Graph(QFrame* parent = nullptr);
    BaseCalc* bc;
    //    QImage image;

    //    QCustomPlot* customPlot;

    int skip;

   protected:
    void paintEvent(QPaintEvent* event);
    void drawGraph(QPainter* pp);
    void drawAxis(QPainter* pp);
    void drawGrid(QPainter* pp);
    //    void drawDraw();

   signals:
};

#endif  // GRAPH_H
