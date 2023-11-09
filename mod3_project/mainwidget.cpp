#include <QtWidgets>
#include "mainwidget.h"
#include "displayCurrenciesWidget.h"
#include "displayExchangeWidget.h"
#include "processing.h"

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
    setAttribute(Qt::WA_DeleteOnClose);

    connect(displayCurrencies_button, SIGNAL(released()), this, SLOT(onPressDisplayCurrenciesButton()));
    connect(displayExchange_button, SIGNAL(released()), this, SLOT(onPressDisplayExchangeButton()));
    connect(convertCurrency_button, SIGNAL(released()), this, SLOT(onPressConvertCurrencyButton()));
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
    DisplayCurrenciesWidget *widget = new DisplayCurrenciesWidget(this);
    widget->resize(400, 500);
    widget->show();
}

void MainWidget::onPressDisplayExchangeButton()
{
    DisplayExchangeWidget* widget = new DisplayExchangeWidget(this);
    widget->resize(400, 500);
    widget->show();
}

void MainWidget::onPressConvertCurrencyButton()
{

    bool amountOk;
    double amountInput = QInputDialog::getDouble(this, tr("Amount"), tr("Starting amount:"), 0, INT_MIN, INT_MAX, 2, &amountOk);

    bool fromCurrencyOk;
    QString fromCurrency = QInputDialog::getText(this, tr("From Currency"), tr("From Currency:"), QLineEdit::Normal, tr("USD"), &fromCurrencyOk);

    bool toCurrencyOk;
    QString toCurrency = QInputDialog::getText(this, tr("To Currency"), tr("To Currency:"), QLineEdit::Normal, tr("PHP"), &toCurrencyOk);

    if (amountOk && fromCurrencyOk && toCurrencyOk) 
    {
        QByteArray fromCurrencyByteArray = fromCurrency.toLatin1();
        QByteArray toCurrencyByteArray = toCurrency.toLatin1();
        std::string output = Processing::convertCurrency(amountInput, fromCurrencyByteArray.data(), toCurrencyByteArray.data());

        QString text;
        if (output != "NULL") 
            text = tr("The converted amount is:\n") + tr(output.c_str());
        else
            text = tr("Input is invalid or there's no network connection!");

        QMessageBox* messageBox = new QMessageBox(this);
        messageBox->setText(text);
        messageBox->setStyleSheet("QLabel{min-width: 400px;}");
        messageBox->setWindowTitle(tr("Converted amount:"));
        messageBox->setAttribute(Qt::WA_DeleteOnClose);
        messageBox->exec();
    }
    else 
    {
        QMessageBox* messageBox = new QMessageBox(this);
        messageBox->setText(tr("Canceled!"));
        messageBox->setStyleSheet("QLabel{min-width: 200px;}");
        messageBox->setWindowTitle(tr("Canceled!"));
        messageBox->setAttribute(Qt::WA_DeleteOnClose);
        messageBox->exec();
    }


}