#include <QtWidgets>
#include "displayExchangeWidget.h"
#include "processing.h"

DisplayExchangeWidget::DisplayExchangeWidget(QWidget* parent) : QDialog(parent)
{

    std::string* res = new std::string;
    *res = Processing::displayExchangeRate();
    label_ = new QLabel(tr(res->c_str()));
    delete res;

    scrollArea = new QScrollArea;
    mainLayout = new QGridLayout;

    scrollArea->setWidget(label_);
    scrollArea->setWidgetResizable(true);
    scrollArea->verticalScrollBar()->setSingleStep(20);
    mainLayout->addWidget(scrollArea);

    setLayout(mainLayout);
    setWindowTitle(tr("Current Exchange Rate"));
    setAttribute(Qt::WA_DeleteOnClose);
    
}

// Destructor
DisplayExchangeWidget::~DisplayExchangeWidget()
{
    delete label_;
    delete scrollArea;
    delete mainLayout;
}
