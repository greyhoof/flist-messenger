#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include "flist_logmetadata.h"

namespace Ui {
    class FAExportDialog;
}

class FAExportDialog : public QDialog {
        Q_OBJECT

    public:
        explicit FAExportDialog(bool debugging = false, QWidget *parent = nullptr);
        ~FAExportDialog();

        void setLogMetaData(QList<FLogMetaData *> logMetaData);

    signals:
        void exportLogsToDestination(QString destination, QString character, bool asZipFile, QString channel = "", QString date = "");

    private slots:
        void buttonCloseTriggered();
        void buttonExportTriggered();
        void buttonBrowseTriggered();
        void checkBoxChannelsAllChanged(int arg1);
        void checkBoxDatesAllChanged(int arg1);

    private:
        bool m_debugging = false;
        Ui::FAExportDialog *ui;
        QList<FLogMetaData *> m_logMetaData;

        QStringList getCharacters();
        QStringList getChannelsForCharacter(QString character);
        QStringList getDatesForCharacterAndChannel(QString character, QString channel);
        QString getPathForCharacterChannelAndDate(QString character, QString channel, QString date);

        void updateCharacterComboBox();
        void updateChannelComboBox();
        void updateLogDateComboBox();
};

#endif // EXPORTDIALOG_H
