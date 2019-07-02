#ifndef MESSAGEDROPPER_H
#define MESSAGEDROPPER_H

#include <QString>

class MessageDropper
{
public:
    MessageDropper();
    void static DropError();
    void static DropThis(QString title, QString msg);
    bool static DropAsk(QString title, QString msg);
};

#endif // MESSAGEDROPPER_H
