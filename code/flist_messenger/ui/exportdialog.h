#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include <QDialog>

namespace Ui {
    class FAExportDialog;
}

class FAExportDialog : public QDialog {
        Q_OBJECT

    public:
        explicit FAExportDialog(QWidget *parent = nullptr);
        ~FAExportDialog();

        void setCharacters(QStringList characters);
        void setChannels(QStringList channels);
        void setLogDates(QStringList logDates);

    signals:
        void requestChannelsForCharacter(QString character);
        void requestLogDatesForCharacterAndChannel(QString character, QString channel);
        void exportLogsToDestination(QString destination, QString character, bool asZipFile, QString channel = "", QString date = "");

    private:
        Ui::FAExportDialog *ui;
        QStringList m_characters;
        QStringList m_channels;
        QStringList m_logDates;

        void updateCharacterComboBox();
        void updateChannelComboBox();
        void updateLogDateComboBox();
};

#endif // EXPORTDIALOG_H
