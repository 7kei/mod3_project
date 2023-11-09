#include <QScrollArea>
#include <QLabel>
#include <QDialog>
#include <QGridLayout>
#include <QScrollBar>
#include "displayCurrenciesWidget.h"
#include "processing.h"

DisplayCurrenciesWidget::DisplayCurrenciesWidget(QWidget* parent) : QDialog(parent)
{

    std::string* res = new std::string;
    *res = Processing::displayCurrencies();
    label_ = new QLabel(tr(res->c_str()));
    delete res;

    scrollArea = new QScrollArea;
    mainLayout = new QGridLayout;

    scrollArea->setWidget(label_);
    scrollArea->setWidgetResizable(true);
    scrollArea->verticalScrollBar()->setSingleStep(20);
    mainLayout->addWidget(scrollArea);

    setLayout(mainLayout);
    setWindowTitle(tr("Supported Currencies"));
    setAttribute(Qt::WA_DeleteOnClose);

}

// Destructor
DisplayCurrenciesWidget::~DisplayCurrenciesWidget()
{
    delete label_;
    delete scrollArea;
    delete mainLayout;
}
