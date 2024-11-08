//
// Created by ark13 on 31.10.2024.
//

#ifndef LAB1_PASSWORDCOPIEDMESSAGE_H
#define LAB1_PASSWORDCOPIEDMESSAGE_H

#include <QWidget>

namespace PasswordCopiedMessage {
    QT_BEGIN_NAMESPACE
    namespace Ui { class PasswordCopiedMessage; }
    QT_END_NAMESPACE

    class PasswordCopiedMessage : public QWidget {
    Q_OBJECT

    public:
        explicit PasswordCopiedMessage(QWidget *parent = nullptr);
        ~PasswordCopiedMessage() override;
        void onShowMessage(const QString &url, const QString &login);

    protected:
        void closeEvent(QCloseEvent *event) override;

    private:
        Ui::PasswordCopiedMessage *ui;

    signals:
        void messageWindowClosed();
    };
} // PasswordCopiedMessage

#endif //LAB1_PASSWORDCOPIEDMESSAGE_H
