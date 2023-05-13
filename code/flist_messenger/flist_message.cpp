#include "flist_message.h"
#include <QSharedData>
#include "flist_global.h"
#include "flist_parser.h"

class FMessageData : public QSharedData {
    public:
        FMessageData()
            : timestamp(QDateTime::currentDateTime()),
              message(),
              messagetype(MESSAGE_TYPE_ERROR),
              sessionid(),
              destinationchannels(),
              destinationcharacters(),
              sourcechannel(),
              sourcecharacter(),
              console(false),
              notify(false),
              broadcast(false),
              stale(true) {}

        QDateTime timestamp;
        QString formattedmessage;
        QString plaintextmessage;
        QString message;
        QString forcedMessage;
        MessageType messagetype;
        QString sessionid;
        QStringList destinationchannels;
        QStringList destinationcharacters;
        QString sourcechannel;
        QString sourcecharacter;
        bool console;
        bool notify;
        bool broadcast;
        bool stale;
};

FMessage::FMessage() : data(new FMessageData) {}

FMessage::FMessage(QString message, MessageType messagetype, bool log) : data(new FMessageData) {
    data->message = message;
    data->messagetype = messagetype;

    shouldLogToDisk = log;
}

FMessage::FMessage(const FMessage &rhs) : data(rhs.data) {}

FMessage &FMessage::operator=(const FMessage &rhs) {
    if (this != &rhs) {
        data.operator=(rhs.data);
    }
    return *this;
}

FMessage::~FMessage() {}

FMessage &FMessage::toUser(bool notify, bool console) {
    data->notify = notify;
    data->console = console;
    return *this;
}

FMessage &FMessage::toBroadcast(bool broadcast) {
    data->broadcast = broadcast;
    return *this;
}

FMessage &FMessage::toChannel(QString channelname) {
    if (!data->destinationchannels.contains(channelname)) {
        data->destinationchannels.append(channelname);
    }
    return *this;
}

FMessage &FMessage::toCharacter(QString charactername) {
    if (!data->destinationcharacters.contains(charactername)) {
        data->destinationcharacters.append(charactername);
    }
    return *this;
}

FMessage &FMessage::fromSession(QString sessionid) {
    data->sessionid = sessionid;
    return *this;
}

FMessage &FMessage::fromChannel(QString channelname) {
    data->sourcechannel = channelname;
    return *this;
}

FMessage &FMessage::fromCharacter(QString charactername) {
    data->sourcecharacter = charactername;
    return *this;
}

QString FMessage::getPlainTextMessage() {
    if (data->stale) {
        getFormattedMessage();
    }
    return data->plaintextmessage;
}

QString FMessage::getFormattedMessage(bool addTimestamp) {
    if (data->stale) {
        BBCodeParser parser;
        QString temp = parser.parse(data->message);
        if (addTimestamp) {
            data->formattedmessage = QString("<small>[%1]</small> %2").arg(data->timestamp.toString("hh:mm:ss AP"), temp);
        } else {
            data->formattedmessage = temp;
        }
        data->plaintextmessage = htmlToPlainText(data->formattedmessage);
        data->stale = false;
    }
    return data->formattedmessage;
}

QString FMessage::getMessage() {
    return data->message;
}

QString FMessage::getForcedMessage() {
    return data->forcedMessage;
}

void FMessage::setForcedMessage(QString _val) {
    // debugMessage(QString("Setting forced message to: %1").arg(_val));

    data->forcedMessage = QString("<small>[%1]</small> %2").arg(data->timestamp.toString("hh:mm:ss AP"), _val);
}

MessageType FMessage::getMessageType() {
    return data->messagetype;
}

bool FMessage::getConsole() {
    return data->console;
}

bool FMessage::getNotify() {
    return data->notify;
}

bool FMessage::getBroadcast() {
    return data->broadcast;
}

QStringList &FMessage::getDestinationChannelList() {
    return data->destinationchannels;
}

QStringList &FMessage::getDestinationCharacterList() {
    return data->destinationcharacters;
}

QString FMessage::getSessionID() {
    return data->sessionid;
}

QString FMessage::getSourceChannel() {
    return data->sourcechannel;
}

QString FMessage::getSourceCharacter() {
    return data->sourcecharacter;
}

QDateTime FMessage::getTimeStamp() {
    return data->timestamp;
}
