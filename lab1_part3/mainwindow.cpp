#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setRowCount(0);
    ui->ClearButton->setEnabled(false);
    ui->PopButton->setEnabled(false);
    ui->LoadDumpData->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::updateTable()
{
    int row = 0;
    ui->tableWidget->setRowCount(stack.get_size());
    if(stack.get_size()==0){
        ui->ClearButton->setEnabled(false);
        ui->PopButton->setEnabled(false);
        ui->LoadDumpData->setEnabled(false);
        return;
    }
    for (auto it = stack.begin(); it != stack.end(); ++it)
    {
        std::string textData = "x: ";
        textData += std::to_string((*it).get_x());
        textData += "    y: ";
        textData += std::to_string((*it).get_y());
        textData += "    height: ";
        textData += std::to_string((*it).get_height());
        if ((*it).what_is_it() == "class Dish")
        {
            textData += "    radius: ";
            textData += std::to_string(((Dish&)(*it)).get_radius());
        }
        else
        {
            textData += "    lenght: ";
            textData += std::to_string(((Sheet&)(*it)).get_lenght());
            textData += "    width: ";
            textData += std::to_string(((Sheet&)(*it)).get_width());
        }

        QTableWidgetItem* cell = new QTableWidgetItem();
        cell->setText(QString::fromStdString(textData));
        ui->tableWidget->setItem(row, 0, cell);
        ui->tableWidget->item(row, 0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

        ++row;
    }
    ui->ClearButton->setEnabled(true);
    ui->PopButton->setEnabled(true);
    ui->LoadDumpData->setEnabled(true);
}


void MainWindow::on_addElement_clicked()
{
    int fieldX = ui->x->text().toInt();
    int fieldY = ui->y->text().toInt();
    int fieldHeight = ui->height->text().toInt();
    int fieldRadius = 0;
    int fieldLenght = 0;
    int fieldWidth = 0;
    if (ui->isDish->isChecked())
    {
        fieldRadius = ui->radius->text().toInt();
        stack.add(Dish(fieldX, fieldY, fieldHeight, fieldRadius));
    }
    else
    {
        fieldLenght = ui->lenght->text().toInt();
        fieldWidth = ui->width->text().toInt();
        stack.add(Sheet(fieldX, fieldY, fieldHeight, fieldLenght, fieldWidth));
    }

    updateTable();
}


void MainWindow::on_PopButton_clicked()
{
    stack.pop();
    updateTable();
}


void MainWindow::on_ClearButton_clicked()
{
    stack.clear();
    updateTable();
}


void MainWindow::on_LoadDumpData_clicked()
{
    std::string path = ui->path->text().toStdString();

    if (ui->isNeedToRead->isChecked())
        stack.read(path);
    else
        stack.write(path);

    updateTable();
}


void MainWindow::on_isNeedToRead_stateChanged(int arg1)
{
    ui->LoadDumpData->setEnabled(arg1 or stack.get_size());
}

