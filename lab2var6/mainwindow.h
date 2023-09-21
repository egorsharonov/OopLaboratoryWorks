#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "HashTable.cpp"
#include <QMainWindow>
#include <iostream>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>

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
    void on_read_clicked();

    void on_write_clicked();

    void on_clear_clicked();

    void on_pop_clicked();

    void on_get_clicked();

    void on_find_clicked();

    void on_add_clicked();

    void on_getRepeats_clicked();

private:
    Ui::MainWindow *ui;
    HashTable<string> table;
    void update();
};
#endif // MAINWINDOW_H
