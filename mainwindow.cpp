#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QGraphicsScene>
#include <QBrush>
#include <QPen>
#include <cmath>

const qreal PARAM = 2.;
const qreal CONST_A = 0.;
const qreal CONST_B = 20.;
const qreal STRETCH = 40.;
const qreal STEP = .01;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene(0, 0, ui->graphicsView->width() - 2, ui->graphicsView->height() - 2, this);
    ui->graphicsView->setScene(scene);
    this->GraphParams.Pen.setColor(Qt::black);
    this->GraphParams.Brush.setColor(Qt::black);
    this->GraphParams.basis_x = scene->width() / 2;
    this->GraphParams.basis_y = scene->height() / 2;
    this->DrawBasis();
    this->DrawGraph();
    //QBrush brush(Qt::black);
    //QPen pen(Qt::black);
    //QLineF line(1, 1, 100, 100);
    //scene->addLine(line, pen);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DrawBasis(void) {
    QGraphicsScene *scene = ui->graphicsView->scene();
    QPen pen(Qt::gray);
    qreal basis[2] = {this->GraphParams.basis_x, this->GraphParams.basis_y};
    QLineF line_x(0, basis[1], scene->width() - 1, basis[1]);
    QLineF line_y(basis[0], 0, basis[0], scene->height() - 1);

    scene->addLine(line_x, pen);
    scene->addLine(line_y, pen);
}

//For Wolfram Alpha:
//x = (3 * 2 * t) / (1 + t^3); y = (3 * 2 * t^2) / (1 + t^3)

qreal MainWindow::FuncX(qreal t) {
    return ((3. * PARAM * t) / (1 + (qreal) pow(t, 3))) * STRETCH;
}
qreal MainWindow::FuncY(qreal t) {
    return -((3. * PARAM * (qreal) pow(t, 2)) / (1 + (qreal) pow(t, 3))) * STRETCH;
}

void MainWindow::DrawGraph(void) {
    QGraphicsScene *scene = ui->graphicsView->scene();
    qreal x[2];
    qreal y[2];
    for (qreal t = CONST_A; t <= CONST_B; t += STEP) {
        if (t == CONST_A) {
            x[0] = FuncX(t);
            y[0] = FuncY(t);
            continue;
        }

        x[1] = x[0];
        y[1] = y[0];
        x[0] = FuncX(t);
        y[0] = FuncY(t);

        qreal shift_x = this->GraphParams.basis_x;
        qreal shift_y = this->GraphParams.basis_y;

        QLineF tmp_line(x[0] + shift_x, y[0] + shift_y, x[1] + shift_x, y[1] + shift_y);
        scene->addLine(tmp_line, this->GraphParams.Pen);
    }
}
