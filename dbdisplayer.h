#ifndef DBDISPLAYER_H
#define DBDISPLAYER_H

#include <QWidget>
#include <QTableWidget>
#include "radio.hpp"
#include <QComboBox>
#include <QItemDelegate>

class DBDisplayer : public QTableWidget
{
    Q_OBJECT
public:
    explicit DBDisplayer(QWidget *parent = nullptr);
    void AddRoleEntity(const Role& role);
    void Reload();

    void resizeEvent(QResizeEvent *event) override;

signals:

};


#endif // DBDISPLAYER_H
