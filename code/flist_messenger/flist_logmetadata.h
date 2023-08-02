#ifndef FLOGMETADATA_H
#define FLOGMETADATA_H

#include <QObject>
#include <QHash>

class FLogMetaData : public QObject {
        Q_OBJECT
    public:
        explicit FLogMetaData(QString character, QObject *parent = nullptr);

        QString getCharacter() { return m_character; };

        void addLogData(QString channel, QString date, QString path);

        QStringList getChannels() { return m_logData.keys(); }

        QStringList getDatesForChannel(QString channel);

        QString getPathForChannelAndDate(QString channel, QString date);

        QList<QPair<QString, QString>> getDatesAndPathsForChannel(QString channel) { return m_logData.value(channel); };

    signals:

    private:
        QString m_character;
        QHash<QString, QList<QPair<QString, QString>>> m_logData;
};

#endif // FLOGMETADATA_H
