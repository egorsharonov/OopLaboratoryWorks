#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Stack.hpp"

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
    void on_addElement_clicked();

    void on_PopButton_clicked();

    void on_ClearButton_clicked();

    void on_LoadDumpData_clicked();

    void on_isNeedToRead_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    Stack stack;

    void updateTable();
};
#endif // MAINWINDOW_H
