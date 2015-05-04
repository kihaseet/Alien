#ifndef LOBBYREGISTERNAME_H
#define LOBBYREGISTERNAME_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class LobbyRegisterName;
}

class LobbyRegisterName : public QWidget
{
    Q_OBJECT

public:
    explicit LobbyRegisterName(QWidget *parent = 0);
    ~LobbyRegisterName();
public slots:
    void slot_wrongName();

private slots:
    void on_pushButton_clicked();

private:
    Ui::LobbyRegisterName *ui;
signals:
    void sendNewName(QString what, QString msg);
};

#endif // LOBBYREGISTERNAME_H
