#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listTable->setColumnCount(1);
    ui->listTable->setRowCount(0);
    ui->popButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_checkBox_stateChanged(int status)
{

    if (status){
        ui->capacityBox->clear();
    }
    ui->capacityBox->setReadOnly(status);
    id_ = (status) ? "Coins" : "Item";
    ui->popButton->setEnabled(list_.getSize());
}


void MainWindow::on_addButton_clicked()
{
    std::string name = ui->nameLineEdit->text().toStdString();
    int price = ui->priceBox->value();
    int capacity;
    bool wrongName = name=="" or name.find_first_not_of("0123456789")==std::string::npos;
    if(wrongName){
        QMessageBox msg;
        msg.setWindowTitle("Error");
        msg.setText("trying to an item with uncorrect name");
        msg.exec();
    }
    else{
        Item* newNode;
        if(id_=="Item"){
            capacity = ui->capacityBox->value();
            newNode = new Item(name,price,capacity);
            list_.push(*newNode);
        }
        else{
            newNode = new Coins(name,price);
            list_.push(*(Coins*)newNode);
        }
        int row = (list_.getSize()==1)? 0 : list_.sort();
        ui->listTable->insertRow(row);
        QTableWidgetItem* it = new QTableWidgetItem();
        std::string data = newNode->getName() + " "
                + std::to_string(newNode->getPrice())
                + " " + std::to_string(newNode->getCapacity());
        it->setText(QString::fromStdString(data));
        ui->listTable->setItem(row,0, it);
        ui->listTable->item(row, 0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
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
    QString name = QFileDialog::getSaveFileName(0,"Save","","*.txt");
    list_.write(name.toStdString());
    QFileInfo check_file(name);
}


void MainWindow::on_readButton_clicked()
{
    std::string name = QFileDialog::getOpenFileName(0,"Open","","*.txt").toStdString();
    list_.read(name);
    int rowCount = list_.getSize();
    ui->listTable->setRowCount(rowCount);
    auto iter=list_.begin();
    for(int row=0; row<rowCount; ++row, ++iter){
        QTableWidgetItem* it = new QTableWidgetItem();
        std::string data = (*iter).getName() + " "
                + std::to_string((*iter).getPrice())
                + " " + std::to_string((*iter).getCapacity());
        it->setText(QString::fromStdString(data));
        ui->listTable->setItem(row,0, it);
        ui->listTable->item(row, 0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }
    ui->popButton->setEnabled(list_.getSize()!=0);
}


