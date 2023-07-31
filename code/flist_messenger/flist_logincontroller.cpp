#include "flist_logincontroller.h"
#include "flist_messenger.h"

FLoginController::FLoginController(FHttpApi::Endpoint *e, FAccount *a, QObject *parent) : QObject(parent), display(0), ep(e), account(a) {
    keyManager = new FKeychainManager(this);

    // clang-format off
    connect(keyManager, SIGNAL(keyStored(QString)), this, SLOT(wroteKey(QString)));
    connect(keyManager, SIGNAL(keyRestored(QString,QString)), this, SLOT(readKey(QString,QString)));
    connect(keyManager, SIGNAL(keyDeleted(QString)), this, SLOT(deletedKey(QString)));
    connect(keyManager, SIGNAL(error(QString)), this, SLOT(keyError(QString)));
    // clang-format on

    loadCredentials();
}

void FLoginController::setWidget(FLoginWindow *w) {
    display = w;
    // clang-format off
    connect(display, SIGNAL(loginRequested(QString,QString,bool)), this, SLOT(requestLogin(QString,QString,bool)));
    // clang-format on
}

void FLoginController::requestLogin(QString username, QString password, bool store) {
    display->setEnabled(false);

    if (store) {
        saveCredentials(username, password);
    } else {
        clearCredentials();
    }

    // clang-format off
    connect(account, SIGNAL(loginError(FAccount*,QString,QString)), this, SLOT(loginError(FAccount*,QString,QString)));
    connect(account, SIGNAL(loginComplete(FAccount*)), this, SLOT(loginComplete(FAccount*)));
    // clang-format on
    account->loginUserPass(username, password);
}

void FLoginController::requestConnect(QString character) {
    static_cast<flist_messenger *>(parent())->startConnect(character);
}

void FLoginController::saveCredentials(QString username, QString password) {
    // generate json from params
    QJsonObject json;
    json.insert("username", username);
    json.insert("password", password);
    QJsonDocument doc(json);
    QString jsonStr(doc.toJson(QJsonDocument::Compact));
    // write it to secure storage
    keyManager->writeKey(QString(CREDENTIAL_KEY), jsonStr);
}

void FLoginController::clearCredentials() {
    keyManager->deleteKey(QString(CREDENTIAL_KEY));
}

void FLoginController::loadCredentials() {
    // request credentials from secure storage
    keyManager->readKey(QString(CREDENTIAL_KEY));
}

void FLoginController::loginError(FAccount *a, QString errorTitle, QString errorMsg) {
    (void)a;
    QString msg = QString("%1: %2").arg(errorTitle, errorMsg);
    display->showError(msg);
    display->clearPassword();
}

void FLoginController::loginComplete(FAccount *a) {
    (void)a;
    display->showConnectPage(account);
    connect(display, SIGNAL(connectRequested(QString)), this, SLOT(requestConnect(QString)));
}

void FLoginController::wroteKey(const QString &key) {
    qDebug() << "loginController->wroteKey() Wrote key successfully: " << key;
}

void FLoginController::readKey(const QString &key, const QString &value) {
    qDebug() << "loginController->readKey() Read key successfully:" << key;
    // qDebug() << "loginController->readKey() Key value (DISABLE THIS):" << value;

    // we only store/load credentials
    if (value.isEmpty()) {
        return;
    }
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(value.toUtf8(), &error);

    if (error.error != QJsonParseError::NoError) {
        qDebug() << "loginController->readKey() Error parsing JSON: " << error.errorString();
        return;
    }

    QJsonObject json = doc.object();
    QString username = json.value("username").toString();
    QString password = json.value("password").toString();
    display->setLoginCredentials(username, password);
}

void FLoginController::deletedKey(const QString &key) {
    qDebug() << "loginController->deletedKey() Deleted key successfully:" << key;
}

void FLoginController::keyError(const QString &error) {
    qDebug() << "loginController->keyError() Key error:" << error;
}
