#include <QApplication>
#include <QDebug>

#include "mainwindow.h"

#include "main.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setWindowIcon( QIcon( ":/icons/application_icon.png" ) );

    LoadFonts();

    MainWindow w;
    w.show();

    return a.exec();
}

void LoadFonts( void )
{
    int id;

    QStringList fonts;

    fonts << ":/fonts/RobotoMono-Bold.ttf";
    fonts << ":/fonts/RobotoMono-Italic.ttf";
    fonts << ":/fonts/RobotoMono-Regular.ttf";

    for ( int i=0; i<fonts.count(); i++ )
    {
        id = QFontDatabase::addApplicationFont( fonts.at( i ) );

        if ( -1 == id )
        {
            qWarning() << fonts.at( i );
        }
    }
}
