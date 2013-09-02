#include "textuipart.h"

#include <kdemacros.h>
#include <kparts/genericfactory.h>

K_PLUGIN_FACTORY(textUIPartFactory, registerPlugin<textUIPart>();)  // produce a factory
K_EXPORT_PLUGIN(textUIPartFactory("hello","hello") )

textUIPart::textUIPart( QWidget *parentWidget, QObject *parent, const QVariantList& )
    : KParts::ReadWritePart(parent)
{
  KGlobal::locale()->insertCatalog("textUI");
  // we need an instance
  setComponentData( textUIPartFactory::componentData() );

  mMainWidget = new QLabel();
  mMainWidget->setText("textui");
  setWidget( mMainWidget );
}

textUIPart::~textUIPart()
{
}
