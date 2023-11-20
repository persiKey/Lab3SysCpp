#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QStatusBar>

#include "radio.hpp"
#include "dbdisplayer.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    DBDisplayer* DBWidget;
    QWidget* centralWidget;

    QVBoxLayout* mainLayout;
    QHBoxLayout* funcRowLayout;
    QVBoxLayout* roleColLayout;
    QVBoxLayout* dutyColLayout;
    QVBoxLayout* reqColLayout;

    QLabel* roleLabel;
    QLabel* roleCodeLabel;
    QLabel* roleNameLabel;
    QLabel* roleWageLabel;

    QSpinBox* roleCodeEdit;
    QTextEdit* roleNameEdit;
    QDoubleSpinBox* roleWageEdit;

    QPushButton* roleAddButton;
    QPushButton* roleRemoveButton;

    QHBoxLayout* roleCodeRow;
    QHBoxLayout* roleNameRow;
    QHBoxLayout* roleWageRow;
    QHBoxLayout* roleControlRow;


    QLabel* dutyLabel;
    QLabel* dutyRCodeLabel;
    QLabel* dutyRDutyLabel;

    QSpinBox* dutyRCodeEdit;
    QTextEdit* dutyRDutyEdit;

    QPushButton* dutyAddButton;
    QPushButton* dutyRemoveButton;

    QHBoxLayout* dutyRCodeRow;
    QHBoxLayout* dutyRDutyRow;
    QHBoxLayout* dutyControlRow;


    QLabel* reqLabel;
    QLabel* reqRCodeLabel;
    QLabel* reqRReqLabel;

    QSpinBox* reqRCodeEdit;
    QTextEdit* reqRReqEdit;

    QPushButton* reqAddButton;
    QPushButton* reqRemoveButton;

    QHBoxLayout* reqRCodeRow;
    QHBoxLayout* reqRReqRow;
    QHBoxLayout* reqControlRow;

    QLabel* wageCodeLabel;
    QSpinBox* wageCodeEdit;

    QLabel* wageDeltaLabel;
    QDoubleSpinBox* wageDeltaEdit;

    QPushButton* promoteButton;
    QPushButton* demoteButton;

    QHBoxLayout* wageControlRow;

    QStatusBar* statusBar;
private:
    void SetUpRoleCol();
    void SetUpDutyCol();
    void SetUpReqCol();
    void SetUpWageRow();

    void SetUpConnections();

    void ShowMessageAndBeep(const QString &text, int timeout = 0);

public slots:
    void RoleAddButtonHandler();
    void RoleRemoveButtonHandler();

    void DutyAddButtonHandler();
    void DutyRemoveButtonHandler();

    void ReqAddButtonHandler();
    void ReqRemoveButtonHandler();

    void WagePromoteButtonHandler();
    void WageDemoteButtonHandler();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void resizeEvent(QResizeEvent *event) override;
};
#endif // MAINWINDOW_H
