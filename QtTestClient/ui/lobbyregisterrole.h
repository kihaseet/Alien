#ifndef LOBBYREGISTERROLE_H
#define LOBBYREGISTERROLE_H

#include <QWidget>
#include "types.h"

namespace Ui {
class LobbyRegisterRole;
}

class LobbyRegisterRole : public QWidget
{
    Q_OBJECT

public:
    explicit LobbyRegisterRole(QWidget *parent = 0);
    ~LobbyRegisterRole();
    void updateButtons(QList<PlayerInfo> player);
    QString CurrRole;

public slots:
    void slot_wrong_role();
private slots:
    void on_Button_Cap_clicked();

    void on_Button_Doc_clicked();

    void on_Button_Gun_clicked();

    void on_Button_Eng_clicked();

    void on_Button_Sci_clicked();

    void on_Button_Sig_clicked();

    void on_Button_Ass_clicked();

    void on_Button_DDoc_clicked();

    void on_Button_DGun_clicked();

    void on_Button_DEng_clicked();

    void on_Button_DSci_clicked();

    void on_Button_DSig_clicked();

    void on_Button_Send_clicked();

private:
    Ui::LobbyRegisterRole *ui;
    QList <QWidget*> buttons;
signals:
    void changeRole(QString wht, QString role);
};

#endif // LOBBYREGISTERROLE_H
