/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include "Widgets/welcomewidget.h"
#include "ui_welcomewidget.h"

#include "acl_global.h"

WelcomeWidget::WelcomeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeWidget)
{
    ui->setupUi(this);

#ifdef USING_FLOAT128
    ui->textBrowser->append("<html><p style=\"font-family:'Open Sans';font-size:16pt;margin-bottom:0px;\">"
                            "Extended Precision</p>"
                            "<p style=\"font-size:11pt;margin-top:0px;margin-bottom:0px;\">&nbsp;</p>"
                            "<p style=\"font-size:11pt;margin-top:0px;\">"
                            "You are currently using Agemarker in the <b>Extended Precision</b> "
                            "mode, which supports up to <b>30</b> decimal precision digits. However, the calculations run in this mode "
                            "take longer to finish compared to the basic Agemarker. If the precision of "
                            "<b>12</b> decimal places is enough for your data, please use the default version of "
                            "the program."
                            "</p></html>");
#endif
}

WelcomeWidget::~WelcomeWidget()
{
    delete ui;
}
