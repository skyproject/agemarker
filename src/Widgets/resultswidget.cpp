#include "resultswidget.h"
#include "ui_resultswidget.h"

ResultsWidget::ResultsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResultsWidget)
{
    ui->setupUi(this);
}

ResultsWidget::~ResultsWidget()
{
    delete ui;
}

ACL::Data::CalculationResultOptions ResultsWidget::getResultOptions()
{
    ACL::Data::CalculationResultOptions options;

    QTreeWidgetItem *approximateFrequency = ui->treeOptions->topLevelItem(0);
    options.includeApproximateFrequencies = (approximateFrequency->checkState(0) == Qt::Checked);
    if (options.includeApproximateFrequencies)
    {
        options.approximateFrequencyPrecision = approximateFrequency->child(0)->child(0)->text(0).toInt();
    }
    QTreeWidgetItem *approximateValues = ui->treeOptions->topLevelItem(1);
    options.includeApproximateValues = (approximateValues->checkState(0) == Qt::Checked);

    delete approximateFrequency;
    delete approximateValues;

    return options;
}

