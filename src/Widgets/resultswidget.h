#ifndef RESULTSWIDGET_H
#define RESULTSWIDGET_H

#include <QWidget>

#include "data.h"

namespace Ui
{
    class ResultsWidget;
}

class ResultsWidget : public QWidget
{
        Q_OBJECT

    public:
        explicit ResultsWidget(QWidget *parent = 0);
        ~ResultsWidget();
        QString getFilePath();
        ACL::Data::CalculationResultOptions getResultOptions();

    private slots:
        void chooseResultsFile();

    private:
        Ui::ResultsWidget *ui;
};

#endif // RESULTSWIDGET_H
