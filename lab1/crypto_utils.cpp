//
// Created by ark13 on 30.10.2024.
//

#include "crypto_utils.h"
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <QString>

QByteArray aes256Encrypt(const QByteArray &plaintext, const QByteArray &key, const QByteArray &iv) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) return {};

    int len;
    int ciphertext_len;
    QByteArray ciphertext(plaintext.size() + EVP_MAX_BLOCK_LENGTH, 0);

    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, reinterpret_cast<const unsigned char *>(key.data()),
                           reinterpret_cast<const unsigned char *>(iv.data())) != 1)
        return {};

    if (EVP_EncryptUpdate(ctx, reinterpret_cast<unsigned char *>(ciphertext.data()), &len,
                          reinterpret_cast<const unsigned char *>(plaintext.data()), plaintext.size()) != 1)
        return {};
    ciphertext_len = len;

    if (EVP_EncryptFinal_ex(ctx, reinterpret_cast<unsigned char *>(ciphertext.data()) + len, &len) != 1)
        return {};
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    ciphertext.resize(ciphertext_len);
    return ciphertext;
}

QByteArray aes256Decrypt(const QByteArray &ciphertext, const QByteArray &key, const QByteArray &iv) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) return {};

    QByteArray plaintext;
    int len = 0;
    int plaintext_len = 0;

    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, reinterpret_cast<const unsigned char *>(key.data()),
                           reinterpret_cast<const unsigned char *>(iv.data())) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return {};
    }

    plaintext.resize(ciphertext.size() + EVP_MAX_BLOCK_LENGTH);

    if (EVP_DecryptUpdate(ctx, reinterpret_cast<unsigned char *>(plaintext.data()), &len,
                          reinterpret_cast<const unsigned char *>(ciphertext.data()), ciphertext.size()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return {};
    }
    plaintext_len = len;

    if (EVP_DecryptFinal_ex(ctx, reinterpret_cast<unsigned char *>(plaintext.data()) + len, &len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return {};
    }
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    plaintext.resize(plaintext_len);
    return plaintext;
}

QByteArray sha256Hash(const QString &input) {
    QByteArray hash(SHA256_DIGEST_LENGTH, 0);
    SHA256(reinterpret_cast<const unsigned char *>(input.toUtf8().data()), input.size(),
           reinterpret_cast<unsigned char *>(hash.data()));
    return hash;
}
