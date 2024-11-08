//
// Created by ark13 on 29.10.2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_DataWindow.h" resolved

#include "datawindow.h"
#include "ui_DataWindow.h"
#include "crypto_utils.h"
#include "passwordcopiedmessage.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QClipboard>
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>

namespace DataWindow {
    DataWindow::DataWindow(QWidget *parent) : QWidget(parent), ui(new Ui::DataWindow) {
        ui->setupUi(this);
        connect(ui->txtSearch, &QLineEdit::textChanged, this, &DataWindow::onSearchTextChanged);
        connect(ui->lstCredentials, &QListWidget::clicked, this, &DataWindow::onItemClick);
    }

    DataWindow::~DataWindow() {
        delete ui;
    }

    void DataWindow::showFilledData(const QByteArray &key, const QByteArray &iv) {
        QFile file("C:/Users/ark13/CLionProjects/lab1/credentials.json");
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, "Ошибка", "Не получается открыть файл с данными.");
            close();
            return;
        }

        QByteArray encryptedData = QByteArray::fromHex(file.readAll());
        file.close();

        QByteArray decryptedData = aes256Decrypt(encryptedData, key, iv);

        QJsonDocument document = QJsonDocument::fromJson(decryptedData);

        QJsonArray data = document.array();

        credentials = QList<QJsonObject>();
        QListWidget *list = ui->lstCredentials;
        for (const auto &i : data) {
            QJsonObject object = i.toObject();
            list->addItem(object["url"].toString());
            list->item(list->count() - 1)->setTextAlignment(Qt::AlignCenter);
            credentials.append(object["credentials"].toObject());
        }
        show();
    }

    void DataWindow::onSearchTextChanged(const QString &query) {
        QListWidget *list = ui->lstCredentials;
        for (int i = 0; i < list->count(); i++) {
            list->setRowHidden(
                i,
                !list->item(i)->text().contains(query, Qt::CaseInsensitive)
            );
        }
    }

    void DataWindow::onItemClicked(int row, const QByteArray &key, const QByteArray &iv) {
        QString url = ui->lstCredentials->item(row)->text();
        QString login = aes256Decrypt(QByteArray::fromHex(credentials[row]["login"].toString().toUtf8()), key, iv);
        QString password = aes256Decrypt(QByteArray::fromHex(credentials[row]["password"].toString().toUtf8()), key, iv);

        QClipboard *clipboard = QGuiApplication::clipboard();
        clipboard->setText(password);

        showPasswordCopiedMessage(url, login);
    }

    void DataWindow::onItemClick(const QModelIndex &index) {
        emit rowClicked(index.row());
    }

    void DataWindow::showPasswordCopiedMessage(const QString &url, const QString &login) {
        passwordCopiedMessage = new PasswordCopiedMessage::PasswordCopiedMessage();
        passwordCopiedMessage->setAttribute(Qt::WA_DeleteOnClose);

        connect(passwordCopiedMessage, &PasswordCopiedMessage::PasswordCopiedMessage::messageWindowClosed, this, &DataWindow::show);
        connect(this, &DataWindow::showMessage, passwordCopiedMessage, &PasswordCopiedMessage::PasswordCopiedMessage::onShowMessage);

        hide();
        emit showMessage(url, login);
    }
} // DataWindow
