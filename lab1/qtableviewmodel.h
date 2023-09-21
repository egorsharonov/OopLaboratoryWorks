#ifndef QTABLEVIEWMODEL_H
#define QTABLEVIEWMODEL_H

#include <QAbstractItemView>
#include "thingslist.h"
#include "coinsstack.h"
#include <QModelIndex>

class QTableViewModel : public QAbstractListModel
{
public:    QTableViewModel(QObject *parent=nullptr);
    int rowCount(const QModelIndex &) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    void populate(QList<CountryFlag> *newValues);
private:
    QList<CountryFlag> *values;
};

#endif // QTABLEVIEWMODEL_H
