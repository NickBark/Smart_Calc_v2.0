#include "customgraph.h"

CustomGraph::CustomGraph(QCustomPlot *parent) : QCustomPlot{parent} {
    setFixedSize(640, 480);
}

void CustomGraph::drawGraph() {
    addGraph();

    xAxis2->setVisible(true);
    xAxis2->setTickLabels(false);
    yAxis2->setVisible(true);
    yAxis2->setTickLabels(false);

    connect(xAxis, SIGNAL(rangeChanged(QCPRange)), xAxis2,
            SLOT(setRange(QCPRange)));
    connect(yAxis, SIGNAL(rangeChanged(QCPRange)), yAxis2,
            SLOT(setRange(QCPRange)));

    graph(0)->setData(x, y);

    graph(0)->rescaleAxes();

    setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    QCPScatterStyle dotScatterStyle;
    dotScatterStyle.setShape(QCPScatterStyle::ssDisc);
    dotScatterStyle.setSize(1);
    graph(0)->setScatterStyle(dotScatterStyle);

    graph(0)->setLineStyle(QCPGraph::lsNone);

    addGraph();

    graph(1)->setData(x2, y2);
    graph(1)->rescaleAxes(true);

    replot();
}
