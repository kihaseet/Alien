#include "lobbyregisterrole.h"
#include "ui_lobbyregisterrole.h"

LobbyRegisterRole::LobbyRegisterRole(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LobbyRegisterRole)
{
    ui->setupUi(this);
    ui->Button_DDoc->setDisabled(true);
    ui->Button_DEng->setDisabled(true);
    ui->Button_DGun->setDisabled(true);
    ui->Button_DSci->setDisabled(true);
    ui->Button_DSig->setDisabled(true);
    ui->Button_Send->setDisabled(true);
    buttons.append(ui->Button_Ass);
    buttons.append(ui->Button_Cap);
    buttons.append(ui->Button_Doc);
    buttons.append(ui->Button_Eng);
    buttons.append(ui->Button_Gun);
    buttons.append(ui->Button_Sci);
    buttons.append(ui->Button_Sig);
}

LobbyRegisterRole::~LobbyRegisterRole()
{
    delete ui;
}

void LobbyRegisterRole::slot_wrong_role(){
    ui->label->setText("Роль указана неверно или уже занята");
}

void LobbyRegisterRole::updateButtons(QList<PlayerInfo> player){
    foreach (QWidget* but, buttons) {
        but->setEnabled(true);
    }
    foreach (PlayerInfo r, player) {
        QString role;
        if(!r.role.isEmpty()) role = r.role.first();

        if(role=="Captain"){
            ui->Button_Cap->setDisabled(true);
            continue;}
        if(role=="Assistant"){
            ui->Button_Ass->setDisabled(true);
            continue;}
        if(role=="Gunmen"){
            ui->Button_Gun->setDisabled(true);
            ui->Button_DGun->setEnabled(true);
            continue;}
        if(role=="Engineer"){
            ui->Button_Eng->setDisabled(true);
            ui->Button_DEng->setEnabled(true);
            continue;}
        if(role=="Scientist"){
            ui->Button_Sci->setDisabled(true);
            ui->Button_DSci->setEnabled(true);
            continue;}
        if(role=="Signalmen"){
            ui->Button_Sig->setDisabled(true);
            ui->Button_DSig->setEnabled(true);
            continue;}
        if(role=="Doctor"){
            ui->Button_Doc->setDisabled(true);
            ui->Button_DDoc->setEnabled(true);
        }
    }
}

void LobbyRegisterRole::on_Button_Cap_clicked()
{
    ui->label->setText("Капитан корабля");
    CurrRole = "Captain";
    ui->Button_Send->setEnabled(true);
}

void LobbyRegisterRole::on_Button_Doc_clicked()
{
    ui->label->setText("Судовой врач");
    CurrRole = "Doctor";
    ui->Button_Send->setEnabled(true);
}

void LobbyRegisterRole::on_Button_Gun_clicked()
{
    ui->label->setText("Начальник службы безопасности");
    CurrRole = "Gunmen";
    ui->Button_Send->setEnabled(true);
}

void LobbyRegisterRole::on_Button_Eng_clicked()
{
    ui->label->setText("Корабельный инженер");
    CurrRole = "Engineer";
    ui->Button_Send->setEnabled(true);
}

void LobbyRegisterRole::on_Button_Sci_clicked()
{
    ui->label->setText("Ученый");
    CurrRole = "Scientist";
    ui->Button_Send->setEnabled(true);
}

void LobbyRegisterRole::on_Button_Sig_clicked()
{
    ui->label->setText("Начальник службы связи");
    CurrRole = "Signalmen";
    ui->Button_Send->setEnabled(true);
}

void LobbyRegisterRole::on_Button_Ass_clicked()
{
    ui->label->setText("Старший помощник");
    CurrRole = "Assistant";
    ui->Button_Send->setEnabled(true);
}

void LobbyRegisterRole::on_Button_DDoc_clicked()
{
    ui->label->setText("Медсестра");
    CurrRole = "Dep_Doctor";
    ui->Button_Send->setEnabled(true);
}

void LobbyRegisterRole::on_Button_DGun_clicked()
{
    ui->label->setText("Офицер службы безопасности");
    CurrRole = "Dep_Gunmen";
    ui->Button_Send->setEnabled(true);
}

void LobbyRegisterRole::on_Button_DEng_clicked()
{
    ui->label->setText("Помощник инженера");
    CurrRole = "Dep_Engineer";
    ui->Button_Send->setEnabled(true);
}

void LobbyRegisterRole::on_Button_DSci_clicked()
{
    ui->label->setText("Лаборант");
    CurrRole = "Dep_Scientist";
    ui->Button_Send->setEnabled(true);
}

void LobbyRegisterRole::on_Button_DSig_clicked()
{
    ui->label->setText("Офицер службы связи");
    CurrRole = "Dep_Signalmen";
    ui->Button_Send->setEnabled(true);
}

void LobbyRegisterRole::on_Button_Send_clicked()
{
    emit changeRole("regrole",CurrRole);
    ui->Button_Send->setDisabled(true);
}
