#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
    class FAExportDialog;
}

class FAExportDialog : public QDialog {
        Q_OBJECT

    public:
        explicit FAExportDialog(bool debugging = false, QWidget *parent = nullptr);
        ~FAExportDialog();

        void setLogMetaData(QHash<QString, QHash<QString, QStringList>> logMetaData);

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
        QHash<QString, QHash<QString, QStringList>> m_logMetaData; // character -> channel list -> log dates

        void updateCharacterComboBox();
        void updateChannelComboBox();
        void updateLogDateComboBox();
};

#endif // EXPORTDIALOG_H
