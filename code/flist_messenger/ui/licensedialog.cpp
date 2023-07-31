#include "licensedialog.h"
#include "ui_licensedialog.h"

FLicenseDialog::FLicenseDialog(QWidget *parent) : QDialog(parent), ui(new Ui::FLicenseDialog) {
    ui->setupUi(this);
}

FLicenseDialog::~FLicenseDialog() {
    delete ui;
}
