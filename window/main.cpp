#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
#include <KUrl>
 
#include "mainwindow.h"
 
int main (int argc, char *argv[])
{
    KAboutData aboutData( "hellopart", "hellopart",
        ki18n("KPart KTp"), "0.1",
        ki18n("hellopart mainwindow."),
        KAboutData::License_GPL,
        ki18n("Copyright (c) 2013 Dan Cohen") );
    KCmdLineArgs::init( argc, argv, &aboutData );
 
    KCmdLineOptions options;
    options.add("+[file]", ki18n("Document to open"));
    KCmdLineArgs::addCmdLineOptions(options);
 
    KApplication app;
 
    MainWindow* window = new MainWindow();
    window->show();
 
    KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
    if(args->count())
    {
        window->load(args->url(0).url());
    }
 
    return app.exec();
}