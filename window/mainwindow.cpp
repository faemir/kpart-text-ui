#include "mainwindow.h"
 
#include <kaction.h>
#include <kactioncollection.h>
#include <kconfig.h>
#include <kedittoolbar.h>
#include <kfiledialog.h>
#include <kshortcutsdialog.h>
#include <klibloader.h>
#include <kmessagebox.h>
#include <kservice.h>
#include <kstandardaction.h>
#include <kstatusbar.h>
#include <kurl.h>
 
#include <QApplication>
 
MainWindow::MainWindow()
    : KParts::MainWindow( )
{
 
    // Setup our actions
    setupActions();
 
    //query the .desktop file to load the requested Part
    KService::Ptr service = KService::serviceByDesktopPath(QString::fromLatin1("textuipart.desktop"));
 
    if (service)
    {
      m_part = service->createInstance<KParts::ReadWritePart>(0);
 
      if (m_part)
      {
            // tell the KParts::MainWindow that this is indeed
            // the main widget
            setCentralWidget(m_part->widget());
 
            setupGUI(ToolBar | Keys | StatusBar | Save);
 
            // and integrate the part's GUI with the shell's
            createGUI(m_part);
      }
      else
      {
          return;//return 1; 
      }
    }
    else
    {
        // if we couldn't find our Part, we exit since the Shell by
        // itself can't do anything useful
        KMessageBox::error(this, QLatin1String("service hellopart not found"));
        qApp->quit();
        // we return here, cause qApp->quit() only means "exit the
        // next time we enter the event loop...
        return;
    }
}
 
MainWindow::~MainWindow()
{
}
 
void MainWindow::load(const KUrl& url)
{
    m_part->openUrl( url );
}
 
void MainWindow::setupActions()
{
    KStandardAction::open(this, SLOT(load()), 
        actionCollection());
    KStandardAction::quit(qApp, SLOT(closeAllWindows()),
        actionCollection());
}
 
void MainWindow::load()
{
    load(KFileDialog::getOpenUrl());
}