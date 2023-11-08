#pragma once

#ifndef DISPLAYEXCHANGEWIDGET_H
#define DISPLAYEXCHANGEWIDGET_H

#include <QWidget>

class QLabel;
class QScrollArea;
class QGridLayout;

class DisplayExchangeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayExchangeWidget(QWidget* parent = 0); //Constructor
    ~DisplayExchangeWidget(); // Destructor

private:
    QLabel* label_;
    QScrollArea* scrollArea;
    QGridLayout* mainLayout;
};

#endif