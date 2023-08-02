#include "exportdialog.h"
#include "ui_exportdialog.h"

FAExportDialog::FAExportDialog(bool debugging, QWidget *parent) : QDialog(parent), ui(new Ui::FAExportDialog) {
    m_debugging = debugging;

    ui->setupUi(this);

    ui->buttonClose->setIcon(QIcon(":/images/cross.png"));

    connect(ui->buttonClose, &QPushButton::clicked, this, &FAExportDialog::buttonCloseTriggered);
    connect(ui->checkBoxChannelsAll, &QCheckBox::stateChanged, this, &FAExportDialog::checkBoxChannelsAllChanged);
    connect(ui->checkBoxDatesAll, &QCheckBox::stateChanged, this, &FAExportDialog::checkBoxDatesAllChanged);
    connect(ui->comboBoxCharacter, &QComboBox::currentIndexChanged, this, [this]() { updateChannelComboBox(); });
    connect(ui->comboBoxChannel, &QComboBox::currentIndexChanged, this, [this]() { updateLogDateComboBox(); });
    connect(ui->buttonExport, &QPushButton::clicked, this, &FAExportDialog::buttonExportTriggered);
    connect(ui->buttonBrowse, &QPushButton::clicked, this, &FAExportDialog::buttonBrowseTriggered);
}

FAExportDialog::~FAExportDialog() {
    delete ui;
}

void FAExportDialog::setLogMetaData(QList<FLogMetaData *> logMetaData) {
    m_logMetaData = logMetaData;
    updateCharacterComboBox();
}

void FAExportDialog::updateCharacterComboBox() {
    ui->comboBoxCharacter->clear();
    ui->comboBoxCharacter->addItems(getCharacters());
    ui->comboBoxCharacter->setCurrentIndex(0);

    updateChannelComboBox();
}

void FAExportDialog::updateChannelComboBox() {
    ui->comboBoxChannel->clear();
    if (m_logMetaData.count() < 1) {
        updateLogDateComboBox();
        return;
    }
    ui->comboBoxChannel->addItems(getChannelsForCharacter(ui->comboBoxCharacter->currentText()));
    ui->comboBoxChannel->setCurrentIndex(0);

    updateLogDateComboBox();
}

void FAExportDialog::updateLogDateComboBox() {
    ui->comboBoxLogDate->clear();
    if (m_logMetaData.count() < 1) {
        updateLogDateComboBox();
        return;
    }

    ui->comboBoxLogDate->addItems(getDatesForCharacterAndChannel(ui->comboBoxCharacter->currentText(), ui->comboBoxChannel->currentText()));
    ui->comboBoxLogDate->setCurrentIndex(0);
}

void FAExportDialog::buttonCloseTriggered() {
    close();
}

void FAExportDialog::buttonExportTriggered() {
    QString selectedCharacter = "";
    QString selectedChannel = "";
    QString selectedLogDate = "";
    QString logPath = "";
    QString destination = ui->lineEditDestination->text();
    bool exportAsZip = ui->checkBoxExportZip->isChecked();

    if (ui->comboBoxCharacter->currentIndex() != -1) {
        selectedCharacter = ui->comboBoxCharacter->currentText();
    }

    if (ui->comboBoxChannel->currentIndex() != -1 && !ui->checkBoxChannelsAll->isChecked()) {
        selectedChannel = ui->comboBoxChannel->currentText();
    }

    if (selectedChannel.length() < 1 && !ui->checkBoxChannelsAll->isChecked()) {
        // TODO: Display error
        return;
    }

    if (ui->comboBoxLogDate->currentIndex() != -1 && !ui->checkBoxDatesAll->isChecked()) {
        selectedLogDate = ui->comboBoxLogDate->currentText();
    }

    logPath = getPathForCharacterChannelAndDate(selectedCharacter, selectedChannel, selectedLogDate);

    if (m_debugging) {
        qDebug() << "Selected Character: " << selectedCharacter;
        qDebug() << "Selected Channel: " << selectedChannel;
        qDebug() << "Selected Log Date: " << selectedLogDate;
        qDebug() << "Log Path: " << logPath;
        qDebug() << "Destination: " << destination;
        qDebug() << "Export as Zip: " << exportAsZip;
    }

    emit exportLogsToDestination(destination, selectedCharacter, exportAsZip, selectedChannel, selectedLogDate);
}

void FAExportDialog::buttonBrowseTriggered() {
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->lineEditDestination->setText(dir);
}

void FAExportDialog::checkBoxChannelsAllChanged(int arg1) {
    if (arg1 == Qt::CheckState::Checked) {
        ui->comboBoxChannel->setEnabled(false);
        // when we export for all channels, we have to export for all dates, too
        ui->checkBoxDatesAll->setChecked(true);
        ui->checkBoxDatesAll->setEnabled(false);
    } else {
        ui->comboBoxChannel->setEnabled(true);
        ui->checkBoxDatesAll->setEnabled(true);
    }
}

void FAExportDialog::checkBoxDatesAllChanged(int arg1) {
    if (arg1 == Qt::CheckState::Checked) {
        ui->comboBoxLogDate->setEnabled(false);
    } else {
        ui->comboBoxLogDate->setEnabled(true);
    }
}

QStringList FAExportDialog::getCharacters() {
    QStringList characters;
    foreach (FLogMetaData *log, m_logMetaData) {
        if (!characters.contains(log->getCharacter())) {
            characters.append(log->getCharacter());
        }
    }

    return characters;
}

QStringList FAExportDialog::getChannelsForCharacter(QString character) {
    QStringList channels;
    foreach (FLogMetaData *log, m_logMetaData) {
        if (log->getCharacter() == character) {
            channels = log->getChannels();
            break;
        }
    }

    return channels;
}

QStringList FAExportDialog::getDatesForCharacterAndChannel(QString character, QString channel) {
    QStringList dates;
    foreach (FLogMetaData *log, m_logMetaData) {
        if (log->getCharacter() == character) {
            dates = log->getDatesForChannel(channel);
            break;
        }
    }

    return dates;
}

QString FAExportDialog::getPathForCharacterChannelAndDate(QString character, QString channel, QString date) {
    QString path;
    foreach (FLogMetaData *log, m_logMetaData) {
        if (log->getCharacter() == character) {
            path = log->getPathForChannelAndDate(channel, date);
            break;
        }
    }

    return path;
}
