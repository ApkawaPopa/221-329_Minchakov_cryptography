//
// Created by ark13 on 29.10.2024.
//

#ifndef LAB1_AUTHWINDOW_H
#define LAB1_AUTHWINDOW_H

#include <QWidget>

namespace AuthWindow {
    QT_BEGIN_NAMESPACE
    namespace Ui { class AuthWindow; }
    QT_END_NAMESPACE

    class AuthWindow : public QWidget {
    Q_OBJECT

    public:
        explicit AuthWindow(QWidget *parent = nullptr);
        ~AuthWindow() override;

    protected:
        void closeEvent(QCloseEvent *event) override;

    private:
        Ui::AuthWindow *ui;
        const QString VALID_PIN = "1234";

    private slots:
        void checkPin();

    signals:
        void pinEntered(const QString &pin);
        void authWindowClosed();
    };
} // AuthWindow

#endif //LAB1_AUTHWINDOW_H
