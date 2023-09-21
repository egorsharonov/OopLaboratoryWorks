#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>


void printCollection(ThingsList& lst) {
    auto it = lst.begin();
    for (int i = 0; i < lst.getSize(); ++i, ++it) {
        std::cout << i+1 << ") " << *it;
    }
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listTable->setColumnCount(1);
    ui->listTable->setRowCount(0);
    ui->popButton->setEnabled(false);
    ui->listTable->horizontalHeader()->setDefaultSectionSize(240);
    ui->listTable->verticalHeader()->setDefaultSectionSize(10);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_checkBox_stateChanged(int status)
{

    if (status){
        ui->volumeBox->clear();
    }
    ui->volumeBox->setReadOnly(status);
    id_ = (status) ? Object::id::coinsStack : Object::id::object;
    ui->popButton->setEnabled(list_.getSize());
}


void MainWindow::on_addButton_clicked()
{
    std::string name = ui->nameLineEdit->text().toStdString();
    int price = ui->priceBox->value();
    int volume = 1;
    Object* newNode;
    if(id_==Object::id::object){
        volume = ui->volumeBox->value();
        if(volume==0 or
           name.find_first_not_of(" \t\n")==std::string::npos){
            QMessageBox msg;
            msg.setWindowTitle("Error");
            msg.setText("wrong name or volume!!!");
            msg.exec();
            return;
        } else{
            newNode = new Object(name,price,volume);
            list_.push(*newNode);
        }
    }
    else{
        newNode = new CoinsStack(name,price);
        list_.push(*(CoinsStack*)newNode);
    }
    if(volume!=0){
        int row = (list_.getSize()==1)? 0 : list_.sort();
        ui->listTable->insertRow(row);
        QTableWidgetItem* it = new QTableWidgetItem();
        std::string data = "name: "+newNode->getName()
                +"  price: "+std::to_string(newNode->getPrice())
                +"  volume: "+std::to_string(newNode->getVolume());
        it->setText(QString::fromStdString(data));
        ui->listTable->setItem(row,0, it);
        ui->listTable->item(row, 0)->setFlags(
                    Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->popButton->setEnabled(list_.getSize());
    }
}


void MainWindow::on_popButton_clicked()
{
    int row = 0;
    if(ui->listTable->selectionModel()->selectedRows().count()){
        row = ui->listTable->currentRow();
    }
    list_.del(row);
    ui->listTable->removeRow(row);
    ui->popButton->setEnabled(list_.getSize());
}

void MainWindow::on_writeButton_clicked()
{
   QString name=QFileDialog::getSaveFileName(0,"Save","","*.txt");
    list_.write(name.toStdString());
}


void MainWindow::on_readButton_clicked()
{
    QString name=QFileDialog::getOpenFileName(0,"Open","","*.txt");
    list_.read(name.toStdString());
    int rowCount = list_.getSize();
    ui->listTable->setRowCount(rowCount);
    auto iter=list_.begin();
    for(int row=0; row<rowCount; ++row, ++iter){
        QTableWidgetItem* it = new QTableWidgetItem();
        std::string data = "name: "+(*iter).getName() +
                "  price: "+ std::to_string((*iter).getPrice())
                + "  volume: "+std::to_string((*iter).getVolume());
        it->setText(QString::fromStdString(data));
        ui->listTable->setItem(row,0, it);
        ui->listTable->item(row, 0)->setFlags(
                    Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }
    ui->popButton->setEnabled(list_.getSize()!=0);
}

