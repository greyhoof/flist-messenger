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
        void setChannels(QHash<QString, QStringList> channels);
        void setLogDates(QHash<QString, QHash<QString, QStringList>> logDates);

    signals:
        void requestChannelsForCharacter(QString character);
        void requestLogDatesForCharacterAndChannel(QString character, QString channel);
        void exportLogsToDestination(QString destination, QString character, bool asZipFile, QString channel = "", QString date = "");

    private slots:
        void on_buttonClose_clicked();

    private:
        Ui::FAExportDialog *ui;
        QStringList m_characters;
        QHash<QString, QStringList> m_channels;                 // character -> channel list
        QHash<QString, QHash<QString, QStringList>> m_logDates; // character -> channel list -> log dates

        void updateCharacterComboBox();
        void updateChannelComboBox();
        void updateLogDateComboBox();
};

#endif // EXPORTDIALOG_H
