//
// Created by ark13 on 30.10.2024.
//

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "crypto_utils.h"

int main() {
    QFile input("C:/Users/ark13/CLionProjects/lab1/credentials_origin.json");
    input.open(QIODevice::ReadOnly);
    QJsonArray data = QJsonDocument::fromJson(input.readAll()).array();
    input.close();

    QByteArray key = sha256Hash("1234");
//    qDebug() << key.toHex();
    QByteArray iv = QByteArray::fromHex("03ac674216f3e15c761ee1a5e255f067");

    QJsonArray encryptedData;
    for (const auto &value : data) {
        QJsonObject obj = value.toObject();
        QJsonObject credentials = obj["credentials"].toObject();

        QByteArray login = credentials["login"].toString().toUtf8();
        QByteArray password = credentials["password"].toString().toUtf8();

        QByteArray encryptedLogin = aes256Encrypt(login, key, iv).toHex();
        QByteArray encryptedPassword = aes256Encrypt(password, key, iv).toHex();

        QJsonObject encryptedCredentials;
        encryptedCredentials["login"] = QString::fromUtf8(encryptedLogin);
        encryptedCredentials["password"] = QString::fromUtf8(encryptedPassword);

        QJsonObject newObj;
        newObj["url"] = obj["url"];
        newObj["credentials"] = encryptedCredentials;

        encryptedData.append(newObj);
    }

    QFile output_intermediate("C:/Users/ark13/CLionProjects/lab1/credentials_login_password_encrypted.json");
    output_intermediate.open(QIODevice::WriteOnly);
    output_intermediate.write(QJsonDocument(encryptedData).toJson());
    output_intermediate.close();

    QFile output("C:/Users/ark13/CLionProjects/lab1/credentials.json");
    output.open(QIODevice::WriteOnly);
    output.write(aes256Encrypt(QJsonDocument(encryptedData).toJson(), key, iv).toHex());
    output.close();

    QByteArray encryptedDocument = aes256Encrypt(QJsonDocument(encryptedData).toJson(), key, iv).toHex();
    qDebug() << "\n\n\n--------------enc-------------\n" << encryptedDocument << "\n--------------enc-------------\n\n\n";

    QByteArray decryptedDocument = aes256Decrypt(QByteArray::fromHex(encryptedDocument), key, iv);
    qDebug() << "\n\n\n--------------dec-------------\n" << decryptedDocument << "\n--------------dec-------------\n\n\n";

    return 0;
}