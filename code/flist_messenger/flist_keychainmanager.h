#ifndef FKEYCHAINMANAGER_H
#define FKEYCHAINMANAGER_H

#include <QObject>
#include <QList>
#include <QTimer>
#include <QHash>

#include <keychain.h>

#define KEY_NAMESPACE "net.f-list.chat"

// Taken from example app provided by QtKeychain library
class FKeychainManager : public QObject {
        Q_OBJECT
    public:
        explicit FKeychainManager(QObject* parent = nullptr);
        void readKey(const QString& key);
        void writeKey(const QString& key, const QString& value);
        void deleteKey(const QString& key);

    Q_SIGNALS:
        void keyStored(const QString& key);
        void keyRestored(const QString& key, const QString& value);
        void keyDeleted(const QString& key);
        void error(const QString& errorText);

    private:
        QKeychain::ReadPasswordJob m_readCredentialJob;
        QKeychain::WritePasswordJob m_writeCredentialJob;
        QKeychain::DeletePasswordJob m_deleteCredentialJob;
};

#endif // FKEYCHAINMANAGER_H
