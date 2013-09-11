#include "textuipart.h"

#include <kdemacros.h>
#include <kparts/genericfactory.h>

#include <QVBoxLayout>
#include "chat-widget.h"

#include <KTp/types.h> //fix this
#include <TelepathyQt/Account>
#include <TelepathyQt/TextChannel>

K_PLUGIN_FACTORY(textUIPartFactory, registerPlugin<textUIPart>();)  // produce a factory
K_EXPORT_PLUGIN(textUIPartFactory("hello","hello") )

textUIPart::textUIPart( QWidget *parentWidget, QObject *parent, const QVariantList& args )
    : KParts::Part(parent)
{
  KGlobal::locale()->insertCatalog(QLatin1String("textUI"));
  // we need an instance
  setComponentData( textUIPartFactory::componentData() );

//   mMainWidget = new QLabel();
//   mMainWidget->setText(QLatin1String("textui"));
//   setWidget( mMainWidget );
  
Tp::AccountPtr account = args[0].value<Tp::AccountPtr>();
Tp::TextChannelPtr textchannel = args[1].value<Tp::TextChannelPtr>();

//     if (account.isNull()) {
//         kDebug() << "Account is nulled";
//         return 0;
//     }
  
QWidget* myMainWidget = new QWidget();
myMainWidget->setLayout(new QVBoxLayout());
myMainWidget->layout()->addWidget(new ChatWidget(textchannel, account, myMainWidget));
setWidget(myMainWidget);
  
}

textUIPart::~textUIPart()
{
}



