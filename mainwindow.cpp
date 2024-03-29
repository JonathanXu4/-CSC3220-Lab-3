#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <iostream>
#include <QPixmap>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , myModel (new MyAddressBookModel(this))
{
    ui->setupUi(this);

    ui->tableView->setModel(myModel);

    // ensures callNumber isn't null to begin with
    callNumber = "";

}

MainWindow::~MainWindow()
{
    delete ui;
}

// Allows the user to select a csv file for use with the program.
void MainWindow::on_actionOpen_an_Address_Book_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Address Book"), "",
        tr("Address Book(*.csv);;All Files (*)"));

    myModel->openFile(fileName);
}

// Allows the user to select phone numbers by clicking on them
void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    callNumber = (myModel->getPhoneNumber(index.row(), index.column()));
    myModel->setFilterString(callNumber);
    ui->numberBox->setText(callNumber);
}

// Adds the given number to the number box, adds dashes, and refreshes the box view
void MainWindow::setNumber(QString num) {
    if (callNumber.length() == 3 || callNumber.length() == 7)
        callNumber = callNumber + "-";
    if (callNumber.length() < 12)
        callNumber = callNumber + num;
    myModel->setFilterString(callNumber);
    ui->numberBox->setText(callNumber);
}

// These methods correspond with the number pad
// sending the related number to the number box
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

// Deletes the last character and all dashes
// refreshes the box view
void MainWindow::on_Delete_clicked()
{
    if (callNumber.length() == 5 || callNumber.length() == 9)
        callNumber = callNumber.left(callNumber.length()-1);
    callNumber = callNumber.left(callNumber.length()-1);
    myModel->setFilterString(callNumber);
    ui->numberBox->setText(callNumber);

}

// If the maximum number of digits are entered, attempt to call
void MainWindow::on_Call_clicked()
{
    if (callNumber.length() == 12) {
        QMessageBox::information(this,tr(""), ("Now calling " + callNumber));
        callNumber = "";
        ui->numberBox->setText(callNumber);
        myModel->setFilterString(callNumber);
    } else {
        QMessageBox::information(this,tr("Error"), tr("Invalid number"));
    }
}

// Closes the program
void MainWindow::on_actionExit_triggered()
{
    close();
}
