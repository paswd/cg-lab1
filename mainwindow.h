#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPen>
#include <QBrush>

namespace Ui {
class MainWindow;
}

class GraphicsParams {
public:
    QPen Pen;
    QBrush Brush;
    qreal basis_x;
    qreal basis_y;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    GraphicsParams GraphParams;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void DrawBasis(void);
    void DrawGraph(void);

    qreal FuncX(qreal t);
    qreal FuncY(qreal t);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
