#include "graph.hpp"

#include "basecalc.h"

Graph::Graph(QFrame* parent) : QFrame{parent} {
    //    image = QImage(640, 640, QImage::Format_RGB32);
    skip = 0;
}

void Graph::paintEvent(QPaintEvent* event) {
    event->accept();
    QPainter p(this);

    drawGrid(&p);
    drawAxis(&p);
    drawGraph(&p);
}

void Graph::drawAxis(QPainter* pp) {
    pp->setPen(QColor(0, 0, 255));
    pp->drawLine(WIDTH / 2, 0, WIDTH / 2, 1000);
    pp->drawLine(0, HEIGHT / 2, 1000, HEIGHT / 2);
}

void Graph::drawGrid(QPainter* pp) {
    int step = 0;

    step = 20;
    pp->setPen(QColor(0, 0, 0, 100));
    double x = 0.;
    x = -bc->scale;
    double x_step = 0.;
    x_step = abs(bc->scale * 2) / 32.;

    for (int i = 0; i < WIDTH; i += step, x += x_step) {
        if (!(i % 80) && i != 0) {
            pp->setPen(QColor(0, 0, 0, 255));
            pp->drawLine(i, 0, i, 1000);
            pp->drawText(i, HEIGHT, QString::number(x, 'g', 3));
        } else {
            pp->setPen(QColor(0, 0, 0, 100));
            pp->drawLine(i, 0, i, 1000);
        }
    }

    step = 20;

    for (int i = 0; i < HEIGHT; i += step) {
        if (!(i % 80) && i != 0) {
            pp->setPen(QColor(0, 0, 0, 255));
            pp->drawLine(0, i, 1000, i);
            if (i == HEIGHT / 2)
                pp->drawText(0, HEIGHT - i, "0");
            else
                pp->drawText(0, HEIGHT - i,
                             QString::number(bc->yNewArr[i], 'g', 3));
        } else {
            pp->setPen(QColor(0, 0, 0, 100));
            pp->drawLine(0, i, 1000, i);
        }
    }
}

void Graph::drawGraph(QPainter* pp) {
    pp->setPen(QColor(255, 0, 0));
    //    pp->drawImage(0, 0, image);
    for (int i = 0; i < bc->num - 2; i++) {
        if (abs(bc->pointArr[i].jy - bc->pointArr[i + 1].jy) >= HEIGHT / 2)
            continue;
        if (!(bc->pointArr[i].error)) {
            pp->drawLine(bc->pointArr[i].ix, bc->pointArr[i].jy,
                         bc->pointArr[i + 1].ix, bc->pointArr[i + 1].jy);
        }
    }
}
