#ifndef MYADDRESSBOOKMODEL_H
#define MYADDRESSBOOKMODEL_H

#include <QAbstractTableModel>
#include <vector>

class MyAddressBookModel: public QAbstractTableModel
{
public:
    MyAddressBookModel(QObject *parent);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    void openFile(QString filePath);
    QString getPhoneNumber(int index, int index2);

    void setFilterString(QString fStr);

private:
    std::vector<QString> names;
    std::vector<QString> lastNames;
    std::vector<QString> phoneNumbers;

    std::vector<int> filteredIndex;

    QString toSequence(QString name);
};

#endif // MYADDRESSBOOKMODEL_H
