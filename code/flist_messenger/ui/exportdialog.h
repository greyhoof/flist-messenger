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

        void setLogMetaData(QHash<QString, QHash<QString, QStringList>> logMetaData);

    signals:
        void exportLogsToDestination(QString destination, QString character, bool asZipFile, QString channel = "", QString date = "");

    private slots:
        void on_buttonClose_clicked();

    private:
        Ui::FAExportDialog *ui;
        QHash<QString, QHash<QString, QStringList>> m_logMetaData; // character -> channel list -> log dates

        void updateCharacterComboBox();
        void updateChannelComboBox();
        void updateLogDateComboBox();
};

#endif // EXPORTDIALOG_H
