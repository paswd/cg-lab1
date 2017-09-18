#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QGraphicsScene>
#include <QBrush>
#include <QPen>
#include <cmath>
#include <QDebug>
#include <QRect>

const qreal PARAM = 2.;
const qreal CONST_A = -.5;
const qreal CONST_B = 30.;
const qreal STRETCH = .14;
const qreal STEP = .01;

const int WINDOW_SPACE = 10;
const int TOP_SPACE = 70;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->GraphParams.SetParams = false;
    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    this->Configure();
    connect(&(this->ResizeTimer), SIGNAL(timeout()), this, SLOT(ResizeCheck()));
    this->ResizeTimer.start();
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
    return ((3. * this->GraphParams.Param * t) / (1 + (qreal) pow(t, 3))) * STRETCH * ui->graphicsView->width();
}
qreal MainWindow::FuncY(qreal t) {
    return -((3. * this->GraphParams.Param * (qreal) pow(t, 2)) / (1 + (qreal) pow(t, 3))) * STRETCH * ui->graphicsView->height();
}

void MainWindow::DrawGraph(void) {
    QGraphicsScene *scene = ui->graphicsView->scene();
    qreal x[2];
    qreal y[2];
    for (qreal t = this->GraphParams.ConstA; t <= this->GraphParams.ConstB; t += STEP) {
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
void MainWindow::Configure(void) {
    this->LastWidth = this->width();
    this->LastHeight = this->height();

    ui->graphicsView->setGeometry(WINDOW_SPACE, WINDOW_SPACE + TOP_SPACE, this->width() - 2 * WINDOW_SPACE, this->height() - 2 * WINDOW_SPACE - TOP_SPACE);
    /*QRect geom_tmp = (ui->Label1->geometry());
    geom_tmp.setY(this->height() - 30);
    ui->Label1->setGeometry(geom_tmp);*/
    //ui->Label1->setGeometry(ui->Label1->geo);
    QGraphicsScene *scene = ui->graphicsView->scene();
    scene->clear();
    scene->setSceneRect(0, 0, ui->graphicsView->width() - 2, ui->graphicsView->height() - 2);
    this->GraphParams.Pen.setColor(Qt::black);
    this->GraphParams.Brush.setColor(Qt::black);
    this->GraphParams.basis_x = scene->width() / 2;
    this->GraphParams.basis_y = scene->height() / 2;
    this->DrawBasis();
    if (this->GraphParams.SetParams) {
        this->DrawGraph();
    }
}
void MainWindow::ResizeCheck(void) {
    if (this->width() != this->LastWidth || this->height() != this->LastHeight) {
        this->Configure();
    }
}

void MainWindow::on_ApplyParams_clicked()
{
    if (ui->ParamA->text().length() == 0 || ui->ParamLeft->text().length() == 0 || ui->ParamLeft->text().length() == 0) {
        return;
    }
    this->GraphParams.Param = ui->ParamA->text().toDouble();
    this->GraphParams.ConstA = ui->ParamLeft->text().toDouble();
    this->GraphParams.ConstB = ui->ParamRight->text().toDouble();
    this->GraphParams.SetParams = true;
    ui->graphicsView->scene()->clear();
    this->DrawBasis();
    this->DrawGraph();
}
