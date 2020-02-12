#include "myaddressbookmodel.h"

#include <QFile>
#include <QMessageBox>
#include <iostream>
#include <QTextStream>

MyAddressBookModel::MyAddressBookModel(QObject *parent)
    :QAbstractTableModel(parent)
{

}

int MyAddressBookModel::rowCount(const QModelIndex &parent) const
{
    return filteredIndex.size();
}

int MyAddressBookModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant MyAddressBookModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        switch(index.column()) {
        case 0:
            return names.at(filteredIndex[index.row()]);
        case 1:
            return phoneNumbers1.at(filteredIndex[index.row()]);
        case 2:
            return phoneNumbers2.at(filteredIndex[index.row()]);
        }
    }
    return QVariant();
}

void MyAddressBookModel::openFile(QString filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
        return;
    }

    QTextStream in(&file);
    names.clear();
    phoneNumbers1.clear();
    phoneNumbers2.clear();

    for (int i = 0; !in.atEnd(); i++) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        if (i == 0) continue;

        names.push_back(fields[0] + " " + fields[1]);

        phoneNumbers1.push_back(fields[7]);

        phoneNumbers2.push_back(fields[8]);

        filteredIndex.push_back(i);
    }
    file.close();

    emit layoutChanged();
}

// Returns phone number 1 if phone number 1 or the name is clicked.
// Otherwise returns phone number 2
QString MyAddressBookModel::getPhoneNumber(int index, int index2)
{
    if (index2 == 0 || index2 == 1)
        return phoneNumbers1.at(filteredIndex[index]);
    return phoneNumbers2.at(filteredIndex[index]);
}

// Filters the address book based on numbers typed in
void MyAddressBookModel::setFilterString(QString fStr)
{
    filteredIndex.clear();
    QString copy = fStr;
    fStr.remove("-");

    for (int i = 0; i < phoneNumbers2.size(); i++) {
        if (phoneNumbers2[i].startsWith(copy) || phoneNumbers1[i].startsWith(copy) || toSequence(names[i]).startsWith(fStr)) {
            filteredIndex.push_back(i);
        }
    }

    emit layoutChanged();
}

// Takes in a QString representing a name and returns its phone number equivalent
QString MyAddressBookModel::toSequence(QString name) {
    QString seq = "";
    for (int i = 0; i < name.length(); i++) {
        if (name[i].toLower() == "a" || name[i].toLower() == "b" || name[i].toLower() == "c")
            seq += "2";
        else if (name[i].toLower() == "d" || name[i].toLower() == "e" || name[i].toLower() == "f")
            seq += "3";
        else if (name[i].toLower() == "g" || name[i].toLower() == "h" || name[i].toLower() == "i")
            seq += "4";
        else if (name[i].toLower() == "j" || name[i].toLower() == "k" || name[i].toLower() == "l")
            seq += "5";
        else if (name[i].toLower() == "m" || name[i].toLower() == "n" || name[i].toLower() == "o")
            seq += "6";
        else if (name[i].toLower() == "p" || name[i].toLower() == "q" || name[i].toLower() == "r" || name[i].toLower() == "s")
            seq += "7";
        else if (name[i].toLower() == "t" || name[i].toLower() == "u" || name[i].toLower() == "v")
            seq += "8";
        else if (name[i].toLower() == "w" || name[i].toLower() == "x" || name[i].toLower() == "y" || name[i].toLower() == "z")
            seq += "9";
    }
    return seq;
}
