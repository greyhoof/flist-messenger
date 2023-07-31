#ifndef LICENSEDIALOG_H
#define LICENSEDIALOG_H

#include <QDialog>

namespace Ui {
    class FLicenseDialog;
}

class FLicenseDialog : public QDialog
{
        Q_OBJECT

    public:
        explicit FLicenseDialog(QWidget *parent = nullptr);
        ~FLicenseDialog();

    private:
        Ui::FLicenseDialog *ui;
};

#endif // LICENSEDIALOG_H
