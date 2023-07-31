#ifndef FLIST_LOGINCONTROLLER_H
#define FLIST_LOGINCONTROLLER_H

#include <QObject>

#include "flist_api.h"
#include "api/endpoint_v1.h"
#include "flist_account.h"
#include "flist_loginwindow.h"
#include "flist_keychainmanager.h"

#define CREDENTIAL_KEY "accounts"

class FLoginWindow;

class FLoginController : public QObject {
        Q_OBJECT
    public:
        explicit FLoginController(FHttpApi::Endpoint *e, FAccount *a, QObject *parent = 0);

        void setWidget(FLoginWindow *w);

    signals:
        void loginSucceeded();
        void loginFailed(QString error_id, QString error_message);
        void connectSucceeded();
        void connectFailed(QString error_id, QString error_message);

    public slots:
        void requestLogin(QString username, QString password, bool store);
        void requestConnect(QString character);
        void saveCredentials(QString username, QString password);
        void clearCredentials();

    private:
        FLoginWindow *display;
        FKeychainManager *keyManager;
        FHttpApi::Endpoint *ep;
        FHttpApi::Request<FHttpApi::TicketResponse> *ticketrequest;
        FAccount *account;

        void loadCredentials();

    private slots:
        void wroteKey(const QString &key);
        void readKey(const QString &key, const QString &value);
        void deletedKey(const QString &key);
        void keyError(const QString &error);

        void loginError(FAccount *a, QString errorTitle, QString errorMsg);
        void loginComplete(FAccount *a);
};

#endif // FLIST_LOGINCONTROLLER_H
