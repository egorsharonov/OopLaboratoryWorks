#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DishQueue.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_open_triggered();

    void on_save_triggered();

    void on_AddIngredient_clicked();

    void on_AddOperation_clicked();

    void update();

    void on_clearButton_clicked();

    void on_delButton_clicked();

private:
    DishQueue queue;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
