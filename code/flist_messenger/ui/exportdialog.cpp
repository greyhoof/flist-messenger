#include "exportdialog.h"
#include "ui_exportdialog.h"

FAExportDialog::FAExportDialog(QWidget *parent) : QDialog(parent), ui(new Ui::FAExportDialog) {
    ui->setupUi(this);

    ui->buttonClose->setIcon(QIcon(":/images/cross.png"));

    connect(ui->comboBoxCharacter, &QComboBox::currentIndexChanged, this, [this]() { updateChannelComboBox(); });
    connect(ui->comboBoxChannel, &QComboBox::currentIndexChanged, this, [this]() { updateLogDateComboBox(); });

    connect(ui->buttonExport, &QPushButton::clicked, this, [this]() {
        QString selectedCharacter = "";
        QString selectedChannel = "";
        QString selectedLogDate = "";
        QString destination = ui->lineEditDestination->text();
        bool exportAsZip = ui->checkBoxExportZip->isChecked();

        if (ui->comboBoxCharacter->currentIndex() != -1) {
            selectedCharacter = ui->comboBoxCharacter->currentText();
        }

        if (selectedChannel.length() < 1) {
            // TODO: Display error
            return;
        }

        if (ui->comboBoxChannel->currentIndex() != -1 && !ui->checkBoxChannelsAll->isChecked()) {
            selectedChannel = ui->comboBoxChannel->currentText();
        }

        if (ui->comboBoxLogDate->currentIndex() != -1 && !ui->checkBoxDatesAll->isChecked()) {
            selectedLogDate = ui->comboBoxLogDate->currentText();
        }

        emit exportLogsToDestination(destination, selectedCharacter, exportAsZip, selectedChannel, selectedLogDate);
    });
}

FAExportDialog::~FAExportDialog() {
    delete ui;
}

void FAExportDialog::setLogMetaData(QHash<QString, QHash<QString, QStringList>> logMetaData) {
    m_logMetaData = logMetaData;
    updateCharacterComboBox();
}

void FAExportDialog::updateCharacterComboBox() {
    ui->comboBoxCharacter->clear();
    ui->comboBoxCharacter->addItems(m_logMetaData.keys());
    ui->comboBoxCharacter->setCurrentIndex(0);

    updateChannelComboBox();
}

void FAExportDialog::updateChannelComboBox() {
    ui->comboBoxChannel->clear();
    if (m_logMetaData.count() < 1) {
        updateLogDateComboBox();
        return;
    }

    QHash<QString, QStringList> channelLogDatesForCharacter = m_logMetaData.value(ui->comboBoxCharacter->currentText());

    ui->comboBoxChannel->addItems(channelLogDatesForCharacter.keys());
    ui->comboBoxChannel->setCurrentIndex(0);

    updateLogDateComboBox();
}

void FAExportDialog::updateLogDateComboBox() {
    ui->comboBoxLogDate->clear();
    if (m_logMetaData.count() < 1) {
        updateLogDateComboBox();
        return;
    }

    ui->comboBoxLogDate->addItems(m_logMetaData.value(ui->comboBoxCharacter->currentText()).value(ui->comboBoxChannel->currentText()));
    ui->comboBoxLogDate->setCurrentIndex(0);
}

void FAExportDialog::on_buttonClose_clicked() {
    close();
}
