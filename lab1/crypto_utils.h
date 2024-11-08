//
// Created by ark13 on 30.10.2024.
//

#ifndef LAB1_CRYPTO_UTILS_H
#define LAB1_CRYPTO_UTILS_H


#include <QByteArray>

QByteArray aes256Encrypt(const QByteArray &plaintext, const QByteArray &key, const QByteArray &iv);

QByteArray aes256Decrypt(const QByteArray &ciphertext, const QByteArray &key, const QByteArray &iv);

QByteArray sha256Hash(const QString &input);


#endif //LAB1_CRYPTO_UTILS_H
