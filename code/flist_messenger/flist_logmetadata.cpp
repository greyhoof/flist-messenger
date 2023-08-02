#include "flist_logmetadata.h"

FLogMetaData::FLogMetaData(QString character, QObject *parent) : QObject{parent} {
    m_character = character;
}

void FLogMetaData::addLogData(QString channel, QString date, QString path) {
    QList<QPair<QString, QString>> datesAndPaths;

    datesAndPaths = m_logData.value(channel);
    datesAndPaths.append(QPair<QString, QString>{date, path});

    m_logData.insert(channel, datesAndPaths);
}

QStringList FLogMetaData::getDatesForChannel(QString channel) {
    QStringList dates;
    QList<QPair<QString, QString>> datesAndPaths;

    datesAndPaths = m_logData.value(channel);
    int count = datesAndPaths.count();
    for (int i = 0; i < count; i++) {
        QPair<QString, QString> item = datesAndPaths.at(i);
        // they should be unique as there's only one log per channel and per day
        dates.append(item.first);
    }

    return dates;
}

QString FLogMetaData::getPathForChannelAndDate(QString channel, QString date) {
    QList<QPair<QString, QString>> datesAndPaths;

    datesAndPaths = m_logData.value(channel);
    int count = datesAndPaths.count();
    for (int i = 0; i < count; i++) {
        QPair<QString, QString> item = datesAndPaths.at(i);
        if (item.first.compare(date) == 0) {
            return item.second;
        }
    }

    return "";
}
