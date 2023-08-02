#ifndef FEXPORTER_H
#define FEXPORTER_H

#include <QObject>
#include <QStringList>
#include <QHash>
#include <QDir>

#include "flist_logmetadata.h"

class FExporter : public QObject {
        Q_OBJECT
    public:
        explicit FExporter(bool debugging = false, QObject *parent = nullptr);
        QList<FLogMetaData *> getLogMetaData();

    signals:

    public slots:
        void onExportLogsToDestination(QString destination, QString character, bool asZipFile, QString channel = "", QString date = "");

    private:
        bool m_debugging = false;

        QStringList getLogFilenames();
        QString getCharacterFromFilename(QString filename);
        QString getChannelFromFilename(QString filename);
        QString getDateFromFilename(QString filename);
};

#endif // FEXPORTER_H
