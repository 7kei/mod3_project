#include <QtWidgets>
#include "displayCurrenciesWidget.h"
#include "processing.h"

DisplayCurrenciesWidget::DisplayCurrenciesWidget(QWidget* parent) : QWidget(parent)
{

    std::string* res = new std::string;
    *res = Processing::displayCurrencies();

    label_ = new QLabel(tr(res->c_str()));

    scrollArea = new QScrollArea;
    mainLayout = new QGridLayout;

    scrollArea->setWidget(label_);
    scrollArea->setWidgetResizable(true);
    scrollArea->verticalScrollBar()->setSingleStep(20);
    mainLayout->addWidget(scrollArea);

    setLayout(mainLayout);
    setWindowTitle(tr("Supported Currencies"));
    setAttribute(Qt::WA_DeleteOnClose);

    delete res;
}

// Destructor
DisplayCurrenciesWidget::~DisplayCurrenciesWidget()
{
    delete label_;
    delete scrollArea;
    delete mainLayout;
}
