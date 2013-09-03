#include "textuipart.h"

#include <kdemacros.h>
#include <kparts/genericfactory.h>

#include "chat-widget.h"

K_PLUGIN_FACTORY(textUIPartFactory, registerPlugin<textUIPart>();)  // produce a factory
K_EXPORT_PLUGIN(textUIPartFactory("hello","hello") )

textUIPart::textUIPart( QWidget *parentWidget, QObject *parent, const QVariantList& )
    : KParts::ReadWritePart(parent)
{
  KGlobal::locale()->insertCatalog(QLatin1String("textUI"));
  // we need an instance
  setComponentData( textUIPartFactory::componentData() );

  mMainWidget = new QLabel();
  mMainWidget->setText(QLatin1String("textui"));
  setWidget( mMainWidget );
  
//QWidget* myMainWidget = new QWidget();
//myMainWidget->setLayout(new QVBoxLayout());
//myMainWidget->addWidget(new chatWidget());
//setWidget(myMainWidget);
  
 //myMainWidget->layout()->addWidget(new ChatWidget());
  
}

textUIPart::~textUIPart()
{
}
