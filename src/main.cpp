/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include <QFontDatabase>
#include <QApplication>

#include "Windows/mainwindow.h"
#include "application.h"

int main ( int argc, char *argv[] )
{
    QApplication a ( argc, argv );

    QCoreApplication::setOrganizationName ( APP_COMPANYNAME_STR );
    QCoreApplication::setOrganizationDomain ( APP_COMPANYNAME_STR );
    QCoreApplication::setApplicationName ( APP_PRODUCTNAME_STR );

    QFontDatabase::addApplicationFont ( "OpenSans-Bold.ttf" );
    QFontDatabase::addApplicationFont ( "OpenSans-Regular.ttf" );

    MainWindow w;
    w.show();

    return a.exec();
}
