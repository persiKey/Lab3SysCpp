#include "mainwindow.h"
#include <QDebug>
#include <limits>
#include <QApplication>
#include <Database.hpp>

using Records::Database;

constexpr auto MAX_ID = std::numeric_limits<int>::max();
constexpr auto MAX_WAGE = std::numeric_limits<double>::max();

void MainWindow::SetUpRoleCol()
{
    roleLabel = new QLabel("Roles", this);
    roleLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    roleCodeLabel = new QLabel("Code:", this);
    roleCodeEdit = new QSpinBox(this);
    roleCodeEdit->setMaximum(MAX_ID);

    roleCodeRow = new QHBoxLayout();
    roleCodeRow->addWidget(roleCodeLabel);
    roleCodeRow->addWidget(roleCodeEdit);

    roleNameLabel = new QLabel("Name:", this);
    roleNameEdit = new QTextEdit(this);
    roleNameEdit->setMaximumSize(roleCodeEdit->size().width(),24);


    roleNameRow = new QHBoxLayout();
    roleNameRow->addWidget(roleNameLabel);
    roleNameRow->addWidget(roleNameEdit);

    roleWageLabel = new QLabel("Wage:", this);
    roleWageEdit = new QDoubleSpinBox(this);
    roleWageEdit->setMaximum(MAX_WAGE);

    roleWageRow = new QHBoxLayout();
    roleWageRow->addWidget(roleWageLabel);
    roleWageRow->addWidget(roleWageEdit);

    roleAddButton = new QPushButton("Add", this);
    roleRemoveButton = new QPushButton("Remove", this);

    roleControlRow = new QHBoxLayout();
    roleControlRow->addWidget(roleAddButton);
    roleControlRow->addWidget(roleRemoveButton);

    roleColLayout = new QVBoxLayout();
    roleColLayout->addWidget(roleLabel);
    roleColLayout->addLayout(roleCodeRow);
    roleColLayout->addLayout(roleNameRow);
    roleColLayout->addLayout(roleWageRow);
    roleColLayout->addLayout(roleControlRow);
}

void MainWindow::SetUpDutyCol()
{
    dutyLabel = new QLabel("Duties", this);
    dutyLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    dutyRCodeLabel = new QLabel("Code:", this);
    dutyRCodeEdit = new QSpinBox(this);
    dutyRCodeEdit->setMaximum(MAX_ID);

    dutyRCodeRow = new QHBoxLayout();
    dutyRCodeRow->addWidget(dutyRCodeLabel);
    dutyRCodeRow->addWidget(dutyRCodeEdit);

    dutyRDutyLabel = new QLabel("Duty:", this);
    dutyRDutyEdit = new QTextEdit(this);
    dutyRDutyEdit->setMaximumSize(dutyRCodeEdit->size().width(),24);

    dutyRDutyRow = new QHBoxLayout();
    dutyRDutyRow->addWidget(dutyRDutyLabel);
    dutyRDutyRow->addWidget(dutyRDutyEdit);

    dutyAddButton = new QPushButton("Add", this);
    dutyRemoveButton = new QPushButton("Remove", this);

    dutyControlRow = new QHBoxLayout();
    dutyControlRow->addWidget(dutyAddButton);
    dutyControlRow->addWidget(dutyRemoveButton);

    dutyColLayout = new QVBoxLayout();
    dutyColLayout->addWidget(dutyLabel);
    dutyColLayout->addLayout(dutyRCodeRow);
    dutyColLayout->addLayout(dutyRDutyRow);
    dutyColLayout->addLayout(dutyControlRow);
}

void MainWindow::SetUpReqCol()
{
    reqLabel = new QLabel("Requirements", this);
    reqLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    reqRCodeLabel = new QLabel("Code:", this);
    reqRCodeEdit = new QSpinBox(this);
    reqRCodeEdit->setMaximum(MAX_ID);

    reqRCodeRow = new QHBoxLayout();
    reqRCodeRow->addWidget(reqRCodeLabel);
    reqRCodeRow->addWidget(reqRCodeEdit);

    reqRCodeLabel = new QLabel("Requirement:", this);
    reqRReqEdit = new QTextEdit(this);
    reqRReqEdit->setMaximumSize(roleCodeEdit->size().width(),24);

    reqRReqRow = new QHBoxLayout();
    reqRReqRow->addWidget(reqRCodeLabel);
    reqRReqRow->addWidget(reqRReqEdit);

    reqAddButton = new QPushButton("Add", this);
    reqRemoveButton = new QPushButton("Remove", this);

    reqControlRow = new QHBoxLayout();
    reqControlRow->addWidget(reqAddButton);
    reqControlRow->addWidget(reqRemoveButton);

    reqColLayout = new QVBoxLayout();
    reqColLayout->addWidget(reqLabel);
    reqColLayout->addLayout(reqRCodeRow);
    reqColLayout->addLayout(reqRReqRow);
    reqColLayout->addLayout(reqControlRow);
}

void MainWindow::SetUpWageRow()
{
    wageCodeLabel = new QLabel("Code:", this);
    wageCodeEdit = new QSpinBox;
    wageCodeEdit->setMaximum(MAX_ID);

    wageDeltaLabel = new QLabel("Sum:", this);
    wageDeltaEdit = new QDoubleSpinBox;
    wageDeltaEdit->setMaximum(MAX_WAGE);

    promoteButton = new QPushButton("Promote");
    demoteButton = new QPushButton("Demote");

    wageControlRow = new QHBoxLayout;
    wageControlRow->addWidget(wageCodeLabel);
    wageControlRow->addWidget(wageCodeEdit);
    wageControlRow->addWidget(wageDeltaLabel);
    wageControlRow->addWidget(wageDeltaEdit);
    wageControlRow->addWidget(promoteButton);
    wageControlRow->addWidget(demoteButton);
}

void MainWindow::SetUpConnections()
{
    connect(roleAddButton, &QPushButton::clicked, this, &MainWindow::RoleAddButtonHandler);
    connect(roleRemoveButton, &QPushButton::clicked, this, &MainWindow::RoleRemoveButtonHandler);

    connect(dutyAddButton, &QPushButton::clicked, this, &MainWindow::DutyAddButtonHandler);
    connect(dutyRemoveButton, &QPushButton::clicked, this, &MainWindow::DutyRemoveButtonHandler);

    connect(reqAddButton, &QPushButton::clicked, this, &MainWindow::ReqAddButtonHandler);
    connect(reqRemoveButton, &QPushButton::clicked, this, &MainWindow::ReqRemoveButtonHandler);

    connect(promoteButton, &QPushButton::clicked, this, &MainWindow::WagePromoteButtonHandler);
    connect(demoteButton, &QPushButton::clicked, this, &MainWindow::WageDemoteButtonHandler);
}

void MainWindow::ShowMessageAndBeep(const QString &text, int timeout)
{
    statusBar->showMessage(text,timeout);
    QApplication::beep();
}

void MainWindow::RoleAddButtonHandler()
{
    try
    {
        Database::GetInstance().addRole(roleCodeEdit->value(),
                                        roleNameEdit->toPlainText().toStdString(),
                                        roleWageEdit->value());
        DBWidget->Reload();
        roleCodeEdit->setValue(roleCodeEdit->value() + 1);
        roleNameEdit->clear();
    }  catch (std::exception &e)
    {
        ShowMessageAndBeep(e.what(),3000);
    }

}

void MainWindow::RoleRemoveButtonHandler()
{
    try
    {
        Database::GetInstance().removeRole(roleCodeEdit->value());
        DBWidget->Reload();
    }  catch (std::exception &e)
    {
        ShowMessageAndBeep(e.what(),3000);
    }
}

void MainWindow::DutyAddButtonHandler()
{
    try
    {
        Database::GetInstance().addDuty(dutyRCodeEdit->value(),
                                               dutyRDutyEdit->toPlainText().toStdString());
        DBWidget->Reload();
        dutyRDutyEdit->clear();
    }  catch (std::exception &e)
    {
        ShowMessageAndBeep(e.what(),3000);
    }
}

void MainWindow::DutyRemoveButtonHandler()
{
    try
    {
        Database::GetInstance().removeDuty(dutyRCodeEdit->value(),
                                               dutyRDutyEdit->toPlainText().toStdString());
        DBWidget->Reload();
        dutyRDutyEdit->clear();
    }  catch (std::exception &e)
    {
        ShowMessageAndBeep(e.what(),3000);
    }
}


void MainWindow::ReqAddButtonHandler()
{
    try
    {
        Database::GetInstance().addRequirement(reqRCodeEdit->value(),
                                               reqRReqEdit->toPlainText().toStdString());
        DBWidget->Reload();
        reqRReqEdit->clear();
    }  catch (std::exception &e)
    {
        ShowMessageAndBeep(e.what(),3000);
    }
}

void MainWindow::ReqRemoveButtonHandler()
{
    try
    {
        Database::GetInstance().removeRequirement(reqRCodeEdit->value(),
                                                  reqRReqEdit->toPlainText().toStdString());
        DBWidget->Reload();
        reqRReqEdit->clear();
    }  catch (std::exception &e)
    {
        ShowMessageAndBeep(e.what(),3000);
    }
}

void MainWindow::WagePromoteButtonHandler()
{
    try
    {
        Database::GetInstance().promoteRole(wageCodeEdit->value(),
                                            wageDeltaEdit->value());
        DBWidget->Reload();
    }  catch (std::exception &e)
    {
        ShowMessageAndBeep(e.what(),3000);
    }
}

void MainWindow::WageDemoteButtonHandler()
{
    try
    {
        Database::GetInstance().demoteRole(wageCodeEdit->value(),
                                            wageDeltaEdit->value());
        DBWidget->Reload();
    }  catch (std::exception &e)
    {
        ShowMessageAndBeep(e.what(),3000);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(640,480);

    mainLayout = new QVBoxLayout;
    funcRowLayout = new QHBoxLayout;
    DBWidget = new DBDisplayer(this);
    statusBar = new QStatusBar(this);

    SetUpRoleCol();
    SetUpDutyCol();
    SetUpReqCol();
    SetUpWageRow();
    SetUpConnections();

    mainLayout->addStretch();
    funcRowLayout->addLayout(roleColLayout);
    funcRowLayout->addLayout(dutyColLayout);
    funcRowLayout->addLayout(reqColLayout);

    mainLayout->addLayout(funcRowLayout);
    mainLayout->addSpacing(5);
    mainLayout->addLayout(wageControlRow);
    mainLayout->addSpacing(5);
    mainLayout->addWidget(DBWidget,1);
    mainLayout->addWidget(statusBar);

    centralWidget = new QWidget;
    this->setCentralWidget(centralWidget);
    centralWidget->setLayout(mainLayout);
    DBWidget->Reload();
}

MainWindow::~MainWindow()
{
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
   roleNameEdit->setMaximumSize(roleCodeEdit->size().width(),24);
   roleWageEdit->setMaximumSize(roleCodeEdit->size());
   dutyRDutyEdit->setMaximumSize(dutyRCodeEdit->size().width(),24);
   reqRReqEdit->setMaximumSize(reqRCodeEdit->size().width(),24);
   wageDeltaEdit->setMaximumSize(dutyRCodeEdit->size());
   wageCodeEdit->setMaximumSize(roleCodeEdit->size());
}

