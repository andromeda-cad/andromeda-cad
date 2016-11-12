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

    id = QFontDatabase::addApplicationFont( ":/fonts/DejaVuSansMono.ttf" );

    if ( -1 == id )
    {
        qWarning() << "Error loading font 'DejaVuSansMono.ttf'";
    }

}
