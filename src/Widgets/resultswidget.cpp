#include <QFileDialog>

#include "resultswidget.h"
#include "ui_resultswidget.h"

ResultsWidget::ResultsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResultsWidget)
{
    ui->setupUi(this);
    connect(ui->buttonChoose, SIGNAL(clicked()),
            this, SLOT(chooseResultsFile()));
}

ResultsWidget::~ResultsWidget()
{
    delete ui;
}

void ResultsWidget::chooseResultsFile()
{
    QFileDialog *fd = new QFileDialog(this, tr("Select file to save calculation results to"));
    fd->setDefaultSuffix(".txt");
    fd->setNameFilter("Text Documents (*.txt)");
    fd->setAcceptMode(QFileDialog::AcceptSave);
    if (fd->exec() == true)
    {
        ui->labelPath->setText(fd->selectedFiles().at(0));
    }
}

Data::ResultsConfiguration ResultsWidget::getResultsConfiguration()
{
    Data::ResultsConfiguration conf;
    conf.path = ui->labelPath->text();
    return conf;
}
