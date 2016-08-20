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
        ACL::Data::CalculationResultOptions getResultOptions();

    private:
        Ui::ResultsWidget *ui;
};

#endif // RESULTSWIDGET_H
