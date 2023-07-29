#include "exportdialog.h"
#include "ui_exportdialog.h"

FAExportDialog::FAExportDialog(QWidget *parent) : QDialog(parent), ui(new Ui::FAExportDialog) {
    ui->setupUi(this);

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

void FAExportDialog::setCharacters(QStringList characters) {
    m_characters = characters;
    updateCharacterComboBox();
}

void FAExportDialog::setChannels(QHash<QString, QStringList> channels) {
    m_channels = channels;
    updateChannelComboBox();
}

void FAExportDialog::setLogDates(QHash<QString, QHash<QString, QStringList>> logDates) {
    m_logDates = logDates;
    updateLogDateComboBox();
}

void FAExportDialog::updateCharacterComboBox() {
    ui->comboBoxCharacter->addItems(m_characters);
    ui->comboBoxCharacter->setCurrentIndex(0);

    updateChannelComboBox();
}

void FAExportDialog::updateChannelComboBox() {
    ui->comboBoxChannel->clear();
    if (m_characters.length() < 1 || m_channels.count() < 1) {
        updateLogDateComboBox();
        return;
    }

    if (!m_channels.contains(ui->comboBoxCharacter->currentText())) {
        updateLogDateComboBox();
        return;
    }

    QStringList channelsForCharacter = m_channels.value(ui->comboBoxCharacter->currentText());

    ui->comboBoxChannel->addItems(channelsForCharacter);
    ui->comboBoxChannel->setCurrentIndex(0);

    updateLogDateComboBox();
}

void FAExportDialog::updateLogDateComboBox() {
    ui->comboBoxLogDate->clear();
    if (m_channels.count() < 1) {
        return;
    }

    if (!m_channels.contains(ui->comboBoxCharacter->currentText()) || !m_logDates.contains(ui->comboBoxCharacter->currentText())
        || !m_logDates.value(ui->comboBoxCharacter->currentText()).contains(ui->comboBoxChannel->currentText())) {
        return;
    }

    ui->comboBoxLogDate->addItems(m_logDates.value(ui->comboBoxCharacter->currentText()).value(ui->comboBoxChannel->currentText()));
    ui->comboBoxLogDate->setCurrentIndex(0);
}
