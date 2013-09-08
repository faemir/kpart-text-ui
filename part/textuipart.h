#ifndef _TEXTUIPART_H_
#define _TEXTUIPART_H_

#include <kparts/part.h>
#include <kparts/factory.h>
#include <QLabel>

#include "chat-widget.h"

class textUIPart : public KParts::Part
{
  Q_OBJECT

  private:
    QLabel *mMainWidget;

public:
    textUIPart(QWidget *parentWidget, QObject *parent, const QVariantList&);

    virtual ~textUIPart();
    bool openFile(){return true;};
    bool saveFile(){return true;};
};

#endif // _TEXTUIPART_H_