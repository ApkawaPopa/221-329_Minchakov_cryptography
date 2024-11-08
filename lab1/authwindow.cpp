//
// Created by ark13 on 29.10.2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_AuthWindow.h" resolved

#include "authwindow.h"
#include "ui_AuthWindow.h"

namespace AuthWindow {
    AuthWindow::AuthWindow(QWidget *parent) : QWidget(parent), ui(new Ui::AuthWindow) {
        ui->setupUi(this);
        connect(ui->btnPin, &QPushButton::clicked, this, &AuthWindow::checkPin);
    }

    AuthWindow::~AuthWindow() {
        delete ui;
    }

    void AuthWindow::checkPin() {
        emit pinEntered(ui->txtPin->text());
        ui->txtPin->setText("");
    }

    void AuthWindow::closeEvent(QCloseEvent *event) {
        emit authWindowClosed();
        ui->txtPin->setText("");
        QWidget::closeEvent(event);
    }
} // AuthWindow
