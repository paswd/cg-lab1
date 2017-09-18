#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPen>
#include <QBrush>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class GraphicsParams {
public:
    QPen Pen;
    QBrush Brush;
    qreal basis_x;
    qreal basis_y;

    qreal ConstA;
    qreal ConstB;
    qreal Param;

    bool SetParams;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    GraphicsParams GraphParams;
    int LastWidth;
    int LastHeight;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void DrawBasis(void);
    void DrawGraph(void);

    void Configure(void);

    qreal FuncX(qreal t);
    qreal FuncY(qreal t);

public slots:
    void ResizeCheck(void);

private slots:
    void on_ApplyParams_clicked();

private:
    Ui::MainWindow *ui;
    QTimer ResizeTimer;
};

#endif // MAINWINDOW_H
