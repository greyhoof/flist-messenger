#include "exportdialog.h"
#include "ui_exportdialog.h"

FAExportDialog::FAExportDialog(QWidget *parent) : QDialog(parent), ui(new Ui::FAExportDialog) {
    ui->setupUi(this);
}

FAExportDialog::~FAExportDialog() {
    delete ui;
}

void FAExportDialog::setCharacters(QStringList characters) {
    m_characters = characters;
    updateCharacterComboBox();
}

void FAExportDialog::updateCharacterComboBox() {
    ui->comboBoxCharacter->addItems(m_characters);
    ui->comboBoxCharacter->setCurrentIndex(0);
    updateChannelComboBox();
}

void FAExportDialog::updateChannelComboBox() {
    ui->comboBoxChannel->clear();
    if (m_characters.length() < 1 || m_channels.length() < 1) {
        updateLogDateComboBox();
        return;
    }

    ui->comboBoxChannel->addItems(m_channels);
    ui->comboBoxChannel->setCurrentIndex(0);
    updateLogDateComboBox();
}

void FAExportDialog::updateLogDateComboBox() {
    ui->comboBoxLogDate->clear();
    if (m_channels.length() < 1) {
        return;
    }

    ui->comboBoxLogDate->addItems(m_logDates);
    ui->comboBoxLogDate->setCurrentIndex(0);
}
