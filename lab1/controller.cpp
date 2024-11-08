//
// Created by ark13 on 31.10.2024.
//

#include <QMessageBox>
#include "controller.h"
#include "crypto_utils.h"


Controller::~Controller() {
    delete authWindow;
    delete dataWindow;
}

Controller::Controller() : QObject() {
    authWindow = new AuthWindow::AuthWindow;
    connect(authWindow, &AuthWindow::AuthWindow::pinEntered, this, &Controller::checkPin);
    connect(authWindow, &AuthWindow::AuthWindow::authWindowClosed, this, &Controller::showData);
    dataWindow = nullptr;
    row = -1;
}

void Controller::showAuth() {
    if (dataWindow) {
        dataWindow->hide();
    }
    authWindow->show();
}

void Controller::showData() {
    if (dataWindow) {
        dataWindow->show();
    }
}

bool Controller::checkPin(const QString &pin) {
    if (pin == VALID_PIN) {
        authWindow->hide();

        QByteArray key = sha256Hash(pin);
        QByteArray iv = QByteArray::fromHex("03ac674216f3e15c761ee1a5e255f067");

        if (dataWindow) {
            dataWindow->onItemClicked(row, key, iv);
        } else {
            dataWindow = new DataWindow::DataWindow;
            connect(dataWindow, &DataWindow::DataWindow::rowClicked, this, &Controller::checkPinRow);
            dataWindow->showFilledData(key, iv);
        }
    } else {
        QMessageBox::warning(authWindow, "Ошибка", "Неверный PIN-код.");
        return false;
    }
}

void Controller::checkPinRow(int rowNumber) {
    this->row = rowNumber;
    showAuth();
}