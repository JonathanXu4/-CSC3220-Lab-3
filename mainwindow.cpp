#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <iostream>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , myModel (new MyAddressBookModel(this))
{
    ui->setupUi(this);

    ui->tableView->setModel(myModel);

    callNumber = "";

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_an_Address_Book_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Address Book"), "",
        tr("Address Book(*.csv);;All Files (*)"));

    std::cout << fileName.toStdString() << std::endl;

    myModel->openFile(fileName);
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    std::cout << index.row() << "," << index.column() << std::endl;
    ui->numberBox->setText((myModel->getPhoneNumber(index.row())));
}

void MainWindow::setNumber(QString num) {
    if (callNumber.length() == 3 || callNumber.length() == 7)
        callNumber = callNumber + "-";
    if (callNumber.length() < 12)
        callNumber = callNumber + num;
    ui->numberBox->setText(callNumber);
}

void MainWindow::on_one_clicked()
{
    setNumber("1");
}

void MainWindow::on_two_clicked()
{
    setNumber("2");
}

void MainWindow::on_three_clicked()
{
    setNumber("3");
}

void MainWindow::on_four_clicked()
{
    setNumber("4");
}

void MainWindow::on_five_clicked()
{
    setNumber("5");
}

void MainWindow::on_six_clicked()
{
    setNumber("6");
}

void MainWindow::on_seven_clicked()
{
    setNumber("7");
}

void MainWindow::on_eight_clicked()
{
    myModel->setFilterString("8");
    setNumber("8");
}

void MainWindow::on_nine_clicked()
{
    setNumber("9");
}


void MainWindow::on_asterisk_clicked()
{
    setNumber("*");
}

void MainWindow::on_zero_clicked()
{
    setNumber("0");
}

void MainWindow::on_pound_clicked()
{
    setNumber("#");
}

void MainWindow::on_Delete_clicked()
{
    if (callNumber.length() == 5 || callNumber.length() == 9)
        callNumber = callNumber.left(callNumber.length()-1);
    callNumber = callNumber.left(callNumber.length()-1);
    ui->numberBox->setText(callNumber);
}
