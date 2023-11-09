#pragma once

#ifndef DISPLAYCURRENCIESWIDGET_H
#define DISPLAYCURRENCIESWIDGET_H

#include <QDialog>

class QLabel;
class QScrollArea;
class QGridLayout;

class DisplayCurrenciesWidget : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayCurrenciesWidget(QWidget* parent = 0); //Constructor
    ~DisplayCurrenciesWidget(); // Destructor

private:
    QLabel* label_;
    QScrollArea* scrollArea;
    QGridLayout* mainLayout;
};

#endif