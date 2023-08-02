#include "flist_exporter.h"
#include "flist_global.h"

FExporter::FExporter(bool debugging, QObject *parent) : QObject{parent} {
    m_debugging = debugging;
}

QList<FLogMetaData *> FExporter::getLogMetaData() {
    QList<FLogMetaData *> logMetaData;

    // we always update the list here because data might have changed between export tool uses
    QStringList fileNames = getLogFilenames();

    foreach (QString file, fileNames) {
        if (file == "." || file == "..") {
            continue;
        }

        QString characterName = getCharacterFromFilename(file);
        QString channelName = getChannelFromFilename(file);
        QString logDate = getDateFromFilename(file);

        FLogMetaData *metaData = new FLogMetaData(characterName, this);
        metaData->addLogData(channelName, logDate, file);

        logMetaData.append(metaData);
    }

    if (m_debugging) {
        foreach (FLogMetaData *data, logMetaData) {
            qDebug().noquote() << "FExporter->getLogMetaData() Character: " << data->getCharacter();
            qDebug().noquote() << "FExporter->getLogMetaData() Channels: " << data->getChannels();
        }
    }

    return logMetaData;
}

void FExporter::onExportLogsToDestination(QString destination, QString character, bool asZipFile, QString channel, QString date) {
    if (m_debugging) {
        qDebug().noquote() << "Exporting logs to: " << destination;
        qDebug().noquote() << "Character: " << character;
        qDebug().noquote() << "Channel: " << channel;
        qDebug().noquote() << "Date: " << date;
        qDebug().noquote() << "As Zip file: " << asZipFile;
    }

    // // get all log files
    // QStringList logFiles = getLogFilenames();

    // // get all log files for character
    // QStringList characterLogFiles = getLogFilenamesForCharacter(logFiles, character);

    // // get all log files for channel
    // QStringList channelLogFiles = getLogFilenamesForChannel(characterLogFiles, channel);

    // // get all log files for date
    // QStringList dateLogFiles = getLogFilenamesForDate(channelLogFiles, date);

    // // copy log files to destination
    // copyLogFilesToDestination(dateLogFiles, destination, asZipFile);
}

QStringList FExporter::getLogFilenames() {
    QStringList dirNames;
    QStringList fileNames;

    dirNames.append("./logs/public/");
    dirNames.append("./logs/private/");
    dirNames.append("./logs/pm/");
    dirNames.append("./logs/console/");

    foreach (QString dir, dirNames) {
        QString dirPath = QDir::toNativeSeparators(dir);
        if (!QDir().exists(dirPath)) {
            debugMessage("FExporter->getCharacterList() Could not find directory: " + dirPath);
            continue;
        }

        QStringList files = QDir(dirPath).entryList(QDir::Files);
        fileNames.append(files);
    }

    return fileNames;
}

QString FExporter::getCharacterFromFilename(QString filename) {
    int indexOfTilde = filename.indexOf("~");
    if (indexOfTilde == -1) {
        debugMessage("FExporter->getCharacterFromFilename() Could not find tilde in filename: " + filename);
        return "";
    }

    if (m_debugging) {
        debugMessage("FExporter->getChannelFromFilename() returning: " + filename.left(indexOfTilde));
    }

    return filename.left(indexOfTilde);
}

QString FExporter::getChannelFromFilename(QString filename) {
    int indexOfTilde = filename.indexOf("~");
    if (indexOfTilde == -1) {
        debugMessage("FExporter->getChannelFromFilename() Could not find ~ in filename");
        return "";
    }

    int indexOfSecondTilde = filename.indexOf("~", indexOfTilde + 1);
    if (indexOfSecondTilde == -1) {
        debugMessage("FExporter->getChannelFromFilename() Could not find second ~ in filename");
        return "";
    }

    if (m_debugging) {
        debugMessage("FExporter->getChannelFromFilename() returning this channel name: " + filename.mid(indexOfTilde + 1, indexOfSecondTilde - indexOfTilde - 1));
    }

    return filename.mid(indexOfTilde + 1, indexOfSecondTilde - indexOfTilde - 1);
}

QString FExporter::getDateFromFilename(QString filename) {
    int indexOfDot = filename.indexOf(".");
    if (indexOfDot == -1) {
        debugMessage("FExporter->getDateFromFilename() Could not find . in filename");
        return "";
    }

    int indexOfTilde = filename.indexOf("~");
    int indexOfSecondTilde = filename.indexOf("~", indexOfTilde + 1);

    if (indexOfTilde == -1 || indexOfSecondTilde == -1) {
        debugMessage("FExporter->getDateFromFilename() Could not find ~ in filename");
        return "";
    }

    if (m_debugging) {
        debugMessage("FExporter->getDateFromFilename() returning this date: " + filename.mid(indexOfSecondTilde + 1, indexOfDot - indexOfSecondTilde - 1));
    }

    return filename.mid(indexOfSecondTilde + 1, indexOfDot - indexOfSecondTilde - 1);
}
