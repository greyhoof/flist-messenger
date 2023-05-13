#ifndef FLIST_MESSAGE_H
#define FLIST_MESSAGE_H

#include "flist_enums.h"
#include <QExplicitlySharedDataPointer>
#include <QString>
#include <QStringList>
#include <QDateTime>

class FMessageData;

class FMessage {
    public:
        FMessage();
        FMessage(QString message, MessageType messagetype, bool log = true);
        FMessage(const FMessage &);
        FMessage &operator=(const FMessage &);
        ~FMessage();

        FMessage &toUser(bool notify = true, bool console = true);
        FMessage &toBroadcast(bool broadcast = true);

        FMessage &toChannel(QString channelname);
        FMessage &toCharacter(QString charactername);

        FMessage &fromSession(QString sessionid);
        FMessage &fromChannel(QString channelname);
        FMessage &fromCharacter(QString charactername);

        QString getPlainTextMessage();
        QString getFormattedMessage(bool addTimestamp = true);
        QString getMessage();

        QString getForcedMessage();

        void setForcedMessage(QString _val);

        MessageType getMessageType();
        bool getConsole();
        bool getNotify();
        bool getBroadcast();

        bool getShouldLogToDisk() { return shouldLogToDisk; };

        QStringList &getDestinationChannelList();
        QStringList &getDestinationCharacterList();
        QString getSessionID();
        QString getSourceChannel();
        QString getSourceCharacter();

        QDateTime getTimeStamp();

        void setShouldLogToDisk(bool _newVal) { shouldLogToDisk = _newVal; }

    private:
        QExplicitlySharedDataPointer<FMessageData> data;
        bool shouldLogToDisk = true;
};

#endif // FLIST_MESSAGE_H
