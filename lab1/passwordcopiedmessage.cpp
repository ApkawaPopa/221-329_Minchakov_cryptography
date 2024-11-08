//
// Created by ark13 on 31.10.2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_PasswordCopiedMessage.h" resolved

#include "passwordcopiedmessage.h"
#include "ui_PasswordCopiedMessage.h"

namespace PasswordCopiedMessage {
    PasswordCopiedMessage::PasswordCopiedMessage(QWidget *parent) :
            QWidget(parent), ui(new Ui::PasswordCopiedMessage) {
        ui->setupUi(this);
    }

    PasswordCopiedMessage::~PasswordCopiedMessage() {
        delete ui;
    }

    void PasswordCopiedMessage::closeEvent(QCloseEvent *event) {
        emit messageWindowClosed();
        QWidget::closeEvent(event);
    }

    void PasswordCopiedMessage::onShowMessage(const QString &url, const QString &login) {
        ui->lblURL->setText(url);
        ui->lblLogin->setText(login);
        show();
    }
} // PasswordCopiedMessage
