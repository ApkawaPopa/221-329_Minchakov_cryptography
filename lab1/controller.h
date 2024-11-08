//
// Created by ark13 on 31.10.2024.
//

#ifndef LAB1_CONTROLLER_H
#define LAB1_CONTROLLER_H


#include "authwindow.h"
#include "datawindow.h"
#include "qobject.h"

class Controller : public QObject {
public:
    Controller();
    ~Controller() override;
    void showAuth();

private:
    DataWindow::DataWindow *dataWindow;
    AuthWindow::AuthWindow *authWindow;
    const QString VALID_PIN = "1234";
    int row;
    void showData();
    bool checkPin(const QString &pin);
    void checkPinRow(int rowNumber);
};


#endif //LAB1_CONTROLLER_H
