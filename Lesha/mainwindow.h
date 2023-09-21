#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "list.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateTable();

private slots:
    void on_checkBox_stateChanged(int arg1);

    void on_addButton_clicked();

    void on_popButton_clicked();

    void on_writeButton_clicked();

    void on_readButton_clicked();

private:
    Ui::MainWindow *ui;
    std::string id_= "Object";
    List list_;
};
#endif // MAINWINDOW_H
