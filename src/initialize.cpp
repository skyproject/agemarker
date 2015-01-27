/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include <QSettings>

#include "Windows/mainwindow.h"
#include "Windows/recoverywindow.h"
#include "application.h"
#include "initialize.h"

#include "sul_softwareupdate.h"

Initialize::Initialize()
{
    /* Check for updates */
    SUL::Structs::Application currentApp;
    currentApp.installedVersion = QString(APP_PRODUCTVERSION_STR);
    currentApp.updateXmlUrl = QUrl("http://www.skyproject.org/static/programs/agemarker/xmlupdate.xml");
    SUL::SoftwareUpdate *su = new SUL::SoftwareUpdate(currentApp);
    connect(su, SIGNAL(finished()),
            this, SLOT(updateCheckFinished()));
}

void Initialize::updateCheckFinished()
{
    QSettings s;
    if (s.contains("ExitedNormally") == true)
    {
        if (s.value("ExitedNormally") == true)
        {
            MainWindow *w = new MainWindow();
            w->show();

            QSettings s;
            s.setValue("ExitedNormally", false);
        }
        else
        {
            RecoveryWindow *rw = new RecoveryWindow();
            rw->show();
        }
    }
    else
    {
        MainWindow *w = new MainWindow();
        w->show();

        QSettings s;
        s.setValue("ExitedNormally", false);
    }
    sender()->deleteLater();
}
