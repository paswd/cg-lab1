#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QGraphicsScene>
#include <QBrush>
#include <QPen>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene(0,0,379,279,this);
    ui->graphicsView->setScene(scene);
    //QBrush brush(Qt::black);
    QPen pen(Qt::black);
    QLineF line(1, 1, 100, 100);
    scene->addLine(line, pen);
}

MainWindow::~MainWindow()
{
    delete ui;
}
