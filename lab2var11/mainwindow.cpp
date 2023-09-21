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
    ui->table->horizontalHeader()->setDefaultSectionSize(500);
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
    tree.read(name.toStdString());
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
    tree.write(name.toStdString());
}


void MainWindow::on_clear_clicked()
{
    tree.clear();
    update();
}


void MainWindow::on_pop_clicked()
{
    int key = ui->currentKey->value();
    try {
        tree.deleteItem(key);
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
    int key = ui->currentKey->value();
    std::string value;
    try {
        value = tree[key];
    } catch (QString err) {
        QMessageBox msg;
        msg.setWindowTitle("Error");
        msg.setText(err);
        msg.exec();
        return;
    }
    ui->value->setText(QString::fromStdString(value));
}


void MainWindow::on_find_clicked()
{
    int key = ui->currentKey->value();
    ui->isExist->setText(tree.find(key)? "True" : "False");
}


void MainWindow::on_add_clicked()
{
    int key = ui->key->value();
    std::string value = ui->data->text().toStdString();
    tree.insertItem(key,value);
    update();
}


void MainWindow::on_getList_clicked()
{
    auto list = tree.lst();
    std::string data;
    for(auto value : list){
        data += " " + value;
    }
    ui->list->setText(QString::fromStdString(data));
}

void MainWindow::update(){
    int row = 0;
    int rowCount=tree.getSize();
    ui->table->setRowCount(rowCount);
    for( auto key : tree.getKeys()){
        auto value = tree[key];
        QString data = "" + QString::number(key) + "  :  " + QString::fromStdString(value);
        QTableWidgetItem* it = new QTableWidgetItem();
        it->setText(data);
        ui->table->setItem(row,0, it);
        ui->table->item(row, 0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ++row;
    }
    bool isNotEmpty = tree.getSize();
    ui->pop->setEnabled(isNotEmpty);
    ui->clear->setEnabled(isNotEmpty);
    ui->write->setEnabled(isNotEmpty);
}
