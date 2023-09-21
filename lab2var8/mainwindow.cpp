#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pop->setEnabled(false);
    ui->clear->setEnabled(false);
    ui->write->setEnabled(false);
    ui->table->setColumnCount(1);
    ui->table->horizontalHeader()->setDefaultSectionSize(370);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_read_clicked()
{
    QString name=QFileDialog::getOpenFileName(0,"Open","","*.txt");
    if(name.isEmpty()){
            QMessageBox msg;
            msg.setWindowTitle("Error");
            msg.setText("file is absent");
            msg.exec();
            return;
        }
    table.read(name.toStdString());
    update();
}


void MainWindow::on_write_clicked()
{
    QString name=QFileDialog::getSaveFileName(0,"Save","","*.txt");
    if(name.isEmpty()){
            QMessageBox msg;
            msg.setWindowTitle("Error");
            msg.setText("empty filename");
            msg.exec();
            return;
        }
    table.write(name.toStdString());
}


void MainWindow::on_clear_clicked()
{
    table.clear();
    update();
}


void MainWindow::on_pop_clicked()
{
    std::string key = ui->currentKey->text().toStdString();
    try {
        table.deleteItem(key);
    } catch (QString err) {
        QMessageBox msg;
        msg.setWindowTitle("Error");
        msg.setText(err);
        msg.exec();
        return;
    }
    update();
}


void MainWindow::on_get_clicked()
{
    std::string key = ui->currentKey->text().toStdString();
    int value;
    try {
        value = table[key];
    } catch (QString err) {
        QMessageBox msg;
        msg.setWindowTitle("Error");
        msg.setText(err);
        msg.exec();
        return;
    }
    ui->value->setText(QString::number(value));
}


void MainWindow::on_find_clicked()
{
    std::string key = ui->currentKey->text().toStdString();
    ui->isExist->setText(table.find(key)? "True" : "False");
}


void MainWindow::on_add_clicked()
{
    std::string key = ui->key->text().toStdString();
    int value = ui->data->value();
    table.insertItem(key,value);
    update();
}


void MainWindow::on_getSum_clicked()
{
    int sum = table.getSum();
    ui->sum->setText(QString::number(sum));
}

void MainWindow::update(){
    int row = 0;
    int rowCount=table.getSize();
    ui->table->setRowCount(rowCount);
    for( auto key : table.getKeys()){
        auto value = table[key];
        QString data = "{ " + QString::fromStdString(key) + ", " + QString::number(value) + " }";
        QTableWidgetItem* it = new QTableWidgetItem();
        it->setText(data);
        ui->table->setItem(row,0, it);
        ui->table->item(row, 0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ++row;
    }
    bool isNotEmpty = table.getSize();
    ui->pop->setEnabled(isNotEmpty);
    ui->clear->setEnabled(isNotEmpty);
    ui->write->setEnabled(isNotEmpty);
}
