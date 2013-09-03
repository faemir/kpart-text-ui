#ifndef _TEXTUIPART_H_
#define _TEXTUIPART_H_

#include <kparts/part.h>
#include <kparts/factory.h>
#include <QLabel>

#include "chat-widget.h"

class textUIPart : public KParts::ReadWritePart
{
  Q_OBJECT

  private:
    QLabel *mMainWidget;

public:
    textUIPart(QWidget *parentWidget, QObject *parent, const QVariantList&);

    QLabel* MainWidget() { return mMainWidget; };

    virtual ~textUIPart();
    bool openFile(){return "hello";};
    bool saveFile(){return "hello";};
};

#endif // _TEXTUIPART_H_