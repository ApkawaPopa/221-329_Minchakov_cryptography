//
// Created by ark13 on 29.10.2024.
//

#ifndef LAB1_DATAWINDOW_H
#define LAB1_DATAWINDOW_H

#include <QWidget>
#include "passwordcopiedmessage.h"

namespace DataWindow {
    QT_BEGIN_NAMESPACE
    namespace Ui { class DataWindow; }
    QT_END_NAMESPACE

    class DataWindow : public QWidget {
    Q_OBJECT

    public:
        explicit DataWindow(QWidget *parent = nullptr);
        ~DataWindow() override;
        void showFilledData(const QByteArray &key, const QByteArray &iv);
        void onItemClicked(int row, const QByteArray &key, const QByteArray &iv);

    private:
        Ui::DataWindow *ui;
        QList<QJsonObject> credentials;
        PasswordCopiedMessage::PasswordCopiedMessage *passwordCopiedMessage;
        void onSearchTextChanged(const QString &query);
        void onItemClick(const QModelIndex &index);
        void showPasswordCopiedMessage(const QString &url, const QString &login);

    signals:
        void showMessage(const QString &url, const QString &login);
        void rowClicked(int row);

    };
} // DataWindow

#endif //LAB1_DATAWINDOW_H
