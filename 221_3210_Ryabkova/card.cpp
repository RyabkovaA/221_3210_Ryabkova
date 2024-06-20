#include "card.h"
#include "ui_card.h"
#include <QRandomGenerator>
#include <QCryptographicHash>
#include <QByteArray>
#include <QDataStream>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <QDebug>

card::card(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::card)
{
    ui->setupUi(this);

    generateNumber();

}

card::~card()
{
    delete ui;
}


void card::on_buttonShow_clicked()
{
    emit cardButtonClicked();
}


void card::showValue()
{
    QByteArray decryptedData = decrypt(m_encryptedNumber);
    QDataStream stream(&decryptedData, QIODevice::ReadOnly);
    ui->labelNumber->setText(QString::number(m_number));
    ui->labelNumber->setHidden(false);
    qDebug() << "Decrypted number:" << m_number;
}

void card::hideNumber()
{
    ui->labelNumber->setHidden(true);
}

int card::cardValue() const
{
    return m_number;
}


void card::generateNumber()
{
    m_number = QRandomGenerator::global()->bounded(-10, 10);
    QByteArray numberArray;
    QDataStream stream(&numberArray, QIODevice::WriteOnly);
    stream << m_number;

    m_encryptedNumber = encrypt(numberArray);


    qDebug() << "Generated number:" << m_number;
    qDebug() << "Encrypted data:" << m_encryptedNumber.toHex();
}

QByteArray card::encrypt(const QByteArray &data)
{
    QByteArray key = QByteArray::fromHex("qwertyuiopasdfghjklzxcvbnm12345678900987654321mnbvcxzqwertyuiopp");
    QByteArray iv = QByteArray::fromHex("000102030405060708090a0b0c0d0e0f");

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
        return QByteArray();

    int len;
    int ciphertext_len;
    unsigned char ciphertext[128];

    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (unsigned char*)key.data(), (unsigned char*)iv.data()))
        return QByteArray();

    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, (unsigned char*)data.data(), data.size()))
        return QByteArray();
    ciphertext_len = len;

    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
        return QByteArray();
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    QByteArray encrypted = QByteArray((char*)ciphertext, ciphertext_len);
    encrypted.prepend(iv);

    qDebug() << "Data to encrypt:" << data.toHex();
    qDebug() << "Encrypted data:" << encrypted.toHex();

    return encrypted;
}

QByteArray card::decrypt(const QByteArray &encryptedData)
{
    QByteArray key = QByteArray::fromHex("qwertyuiopasdfghjklzxcvbnm12345678900987654321mnbvcxzqwertyuiopp");
    // QByteArray key = QByteArray::fromHex("00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff");
    QByteArray iv = encryptedData.left(16);
    QByteArray ciphertext = encryptedData.mid(16);

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
        return QByteArray();

    int len;
    int plaintext_len;
    unsigned char plaintext[128];

    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (unsigned char*)key.data(), (unsigned char*)iv.data()))
        return QByteArray();

    if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, (unsigned char*)ciphertext.data(), ciphertext.size()))
        return QByteArray();
    plaintext_len = len;

    if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
        return QByteArray();
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    QByteArray decrypted = QByteArray((char*)plaintext, plaintext_len);

    qDebug() << "Encrypted data:" << encryptedData.toHex();
    qDebug() << "Decrypted data:" << decrypted.toHex();

    return decrypted;
}

