#include "dbdisplayer.h"
#include "Database.hpp"
#include <sstream>

DBDisplayer::DBDisplayer(QWidget *parent) : QTableWidget(parent)
{
    QStringList Headers = {"Code", "Name","Wage", "Duties", "Requirements"};
    this->setColumnCount(Headers.size());
    this->setHorizontalHeaderLabels(Headers);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->resize(500,500);

}

void DBDisplayer::AddRoleEntity(const Role &role)
{
    auto currentRow = rowCount();
    insertRow(currentRow);

    setItem( currentRow,
                             0,
                             new QTableWidgetItem(QString::number(role.getCode())));
    setItem( currentRow,
                             1,
                             new QTableWidgetItem(QString::fromStdString(role.getName())));
    setItem(currentRow,
                             2,
                             new QTableWidgetItem(QString::number(role.getWage())));
    std::stringstream DutiesList;
    for(const auto & d : role.getDuties())
    {
        DutiesList << d << ';';
    }
    auto DutiesStr = DutiesList.str();
    DutiesStr.pop_back();
    setItem(currentRow,
                             3,
                             new QTableWidgetItem(QString::fromStdString(DutiesStr)));

    std::stringstream ReqList;
    for(const auto & d : role.getRequirements())
    {
        ReqList << d << ';';
    }
    auto ReqStr = ReqList.str();
    ReqStr.pop_back();
    setItem(currentRow,
                             4,
                             new QTableWidgetItem(QString::fromStdString(ReqStr)));

    this->resizeRowToContents(currentRow);
}

void DBDisplayer::Reload()
{
    this->reset();
    this->setRowCount(0);
    for(const auto& role : Records::Database::GetInstance().getAllRoles())
    {
        AddRoleEntity(role);
    }
}

void DBDisplayer::resizeEvent(QResizeEvent *event)
{
    this->setColumnWidth(0, this->width()/8.8);
    this->setColumnWidth(1, this->width()/4);
    this->setColumnWidth(2, this->width()/8.8);
    this->setColumnWidth(3, this->width()/4);
    this->setColumnWidth(4, this->width()/4);
}


