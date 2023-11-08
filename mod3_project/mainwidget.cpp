#include <QtWidgets>
#include "mainwidget.h"
#include "displayCurrenciesWidget.h"
#include "displayExchangeWidget.h"

// Constructor for main widget
MainWidget::MainWidget(QWidget* parent) : QWidget(parent)
{

    label_ = new QLabel(tr("Welcome to the Billing System!"));
    displayCurrencies_button = new QPushButton(tr("Display Supported Currencies"));
    displayExchange_button = new QPushButton(tr("Display Current Exchange Rate"));
    convertCurrency_button = new QPushButton(tr("Convert Currencies"));

    label_->setAlignment(Qt::AlignCenter);

    mainLayout = new QGridLayout;

    mainLayout->addWidget(label_, 0, 0);
    mainLayout->addWidget(displayCurrencies_button, 1, 0);
    mainLayout->addWidget(displayExchange_button, 2, 0);
    mainLayout->addWidget(convertCurrency_button, 3, 0);

    setLayout(mainLayout);
    setWindowTitle(tr("Billing System"));

    connect(displayCurrencies_button, SIGNAL(released()), this, SLOT(onPressDisplayCurrenciesButton()));
    connect(displayExchange_button, SIGNAL(released()), this, SLOT(onPressDisplayExchangeButton()));
}

// Destructor
MainWidget::~MainWidget()
{
    delete label_;
    delete displayCurrencies_button;
    delete displayExchange_button;
    delete convertCurrency_button;
    delete mainLayout;
}

void MainWidget::onPressDisplayCurrenciesButton()
{
    DisplayCurrenciesWidget *widget = new DisplayCurrenciesWidget();
    widget->resize(400, 500);
    widget->show();
}

void MainWidget::onPressDisplayExchangeButton()
{
    DisplayExchangeWidget* widget = new DisplayExchangeWidget();
    widget->resize(400, 500);
    widget->show();
}