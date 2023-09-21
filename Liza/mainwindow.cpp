#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DishQueue.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->clearButton->setEnabled(false);
    ui->delButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_open_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Choose File","","*.txt");
    if(fileName.isEmpty()){
        QMessageBox msg;
        msg.setWindowTitle("Error");
        msg.setText("no file!!!");
        msg.exec();
        return;
    }
    queue.read(fileName.toStdString());
    update();
    ui->clearButton->setEnabled(queue.getSize() != 0);
    ui->delButton->setEnabled(queue.getSize() != 0);
}

void MainWindow::on_save_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save the file");
    queue.write(fileName.toStdString());
    update();
}

void MainWindow::on_AddIngredient_clicked()
{
    string name = ui->NameIng->text().toStdString();
    string unit = ui->Unit->text().toStdString();
    int amount = ui->Amount->value();
    queue.pushBack(new Dish(name, unit, amount));
    update();
    ui->clearButton->setEnabled(true);
    ui->delButton->setEnabled(true);
}

void MainWindow::on_AddOperation_clicked()
{
    string name = ui->NameIng->text().toStdString();
    string unit = ui->Unit->text().toStdString();
    int amount = ui->Amount->value();
    std::string oper = ui->Operation->currentText().toStdString();
    Operation::actions act;
    if(oper == "pack"){
        act = Operation::actions::pack;
    }else if(oper == "fry"){
        act = Operation::actions::fry;
    }else if(oper == "put"){
        act = Operation::actions::put;
    }else if(oper == "cut"){
        act = Operation::actions::cut;
    } else{
        act = Operation::actions::none;
    }
    int duration = ui->Duration->value();
    queue.pushBack(new Operation(name, unit, amount, act, duration));
    update();
    ui->clearButton->setEnabled(true);
    ui->delButton->setEnabled(true);
}

void MainWindow::update()
{
    ui->TextBrowser->clear();
    QString data;
    for(auto iter = queue.begin(); iter != nullptr; ++iter){
        data += QString::fromStdString((*iter).getName() + "  ");
        data += QString::number((*iter).getAmount()) + "  ";
        data += QString::fromStdString((*iter).getUnit());
        if((*iter).identity() == Dish::id::operation){
            int act = ((Operation*)&*iter)->getAction();
            QString actions[] = {"cut","pack","fry","put","none"};
            data += "  " + actions[act] + "  ";
            data += QString::number(((Operation*)&*iter)->getDuration()) + "\n";
        } else{
            data += "\n";
        }
    }
    ui->TextBrowser->setText(data);
}


void MainWindow::on_clearButton_clicked()
{
   queue.clear();
   update();
   ui->clearButton->setEnabled(false);
   ui->delButton->setEnabled(false);
}

void MainWindow::on_delButton_clicked()
{
   queue.popFront();
   update();
   ui->clearButton->setEnabled(queue.getSize() != 0);
   ui->delButton->setEnabled(queue.getSize() != 0);
}
