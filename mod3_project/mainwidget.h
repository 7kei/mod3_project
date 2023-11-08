#pragma once

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

class QPushButton;
class QLabel;
class QMessageBox;
class QGridLayout;

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget* parent = 0); //Constructor
    ~MainWidget(); // Destructor

private slots:
    void onPressDisplayCurrenciesButton();
    void onPressDisplayExchangeButton();

private:
    QLabel* label_;
    QGridLayout* mainLayout;
    QPushButton* displayCurrencies_button;
    QPushButton* displayExchange_button;
    QPushButton* convertCurrency_button;
};

#endif ==