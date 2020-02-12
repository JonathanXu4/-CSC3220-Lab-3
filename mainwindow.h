#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <myaddressbookmodel.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QString callNumber;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_an_Address_Book_triggered();

    void on_tableView_clicked(const QModelIndex &index);

    void on_eight_clicked();

    void on_one_clicked();

    void setNumber(QString num);

    void on_two_clicked();

    void on_three_clicked();

    void on_four_clicked();

    void on_five_clicked();

    void on_six_clicked();

    void on_seven_clicked();

    void on_nine_clicked();

    void on_asterisk_clicked();

    void on_zero_clicked();

    void on_pound_clicked();

    void on_Delete_clicked();

    void on_Call_clicked();

private:
    Ui::MainWindow *ui;
    MyAddressBookModel *myModel;
};
#endif // MAINWINDOW_H
