#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    day=0;
    ui->ButtonCancer->hide();

    inventory = new Inventory(this);
    actions = new Actions(this);
    log = new Log(this);
    status = new Status(this);
    playerlist = new PlayerList(this);
    targets = new Targets(this);

    stackedWidgetInventory = new QStackedWidget(this);
    stackedWidgetInventory->addWidget(actions);
    stackedWidgetInventory->addWidget(inventory);
    ui->LayoutActions->addWidget(stackedWidgetInventory);
    stackedWidgetInventory->setCurrentIndex(0);

    stackedWidgetMain = new QStackedWidget(this);
    stackedWidgetMain->addWidget(playerlist);
    stackedWidgetMain->addWidget(log);
    stackedWidgetMain->addWidget(targets);
    ui->LayoutPlayerList->addWidget(stackedWidgetMain);
    stackedWidgetMain->setCurrentIndex(0);


}

void Game::StartGame( QMap<QString, PlayerInfo> play){
    //  playerlist->startGame(QMap<QString, PlayerInfo> play);
}

Game::~Game()
{
    delete ui;
}



void Game::on_pushButton_clicked()
{
    if(stackedWidgetInventory->currentIndex()==0){
        ui->pushButton->setText("Закрыть");
        stackedWidgetInventory->setCurrentIndex(1);
    }else{
        ui->pushButton->setText("Инвентарь");
        stackedWidgetInventory->setCurrentIndex(0);
    }
}

void Game::updateActions(QVector<TurnObject> ActionsVector){
    foreach (TurnObject var, ActionsVector) {
        if(var.type!=TT_VOTE && var.type!=TT_VOTE){
            QPushButton* tmp;
            if(TurnObjectPool.contains(var)){
                tmp = TurnObjectPool[var];
                TurnObjectPool.remove(var);
                TurnObjectPool.insert(var,tmp);
            }else{
                tmp = new QPushButton(this);
                connect(tmp,SIGNAL(clicked()),this,SLOT(PrepareTurn()));
                QString txt;
                switch (var.type)
                {
                case TT_ULT_ITEM:
                    txt = "U"+var.item;
                    break;
                case TT_USE_ITEM:
                    txt = var.item;
                    break;
                case TT_ATTACK:
                    txt = "Напасть";
                    break;
                case TT_INFECT:
                    txt = "Заразить";
                    break;
                case TT_UP:
                    txt = "Выйти из ванны" ;
                    break;
                case TT_DOWN:
                    txt = "Лечь в ванну";
                    break;
                case TT_SKIP:
                    txt = "Ждать" ;
                    break;
                }
                tmp->setText(txt);
                TurnObjectPool.insert(var,tmp);
            }
            if(!CurrentButtons.contains(tmp)){
                (var.type==TT_USE_ITEM || var.type==TT_ULT_ITEM) ?
                            inventory->AddButton(tmp)
                          : actions->AddButton(tmp);
                CurrentButtons.append(tmp);
            }
        }
        /*else if(var.type==TT_VOTE){
            foreach (QString player, playerlist->playlist) {
                if(var.targets.contains(player)){
                    playerlist->playlist[player]->showVoteButton(true);
                }else playerlist->playlist[player]->showVoteButton(false);
            }
        }*/
        /*else if(var.type==TT_UNVOTE){
            foreach (PlayerWidget player, playerlist->playlist.values()) {
                player.showUnVoteButton(player.YetVoting);
            }
        }*/
    }
    foreach (QPushButton* button, CurrentButtons) {
        if(!ActionsVector.contains(TurnObjectPool.key(button)))
        {
            (TurnObjectPool.key(button).type==TT_USE_ITEM || TurnObjectPool.key(button).type==TT_ULT_ITEM) ?
                        inventory->RemoveButton(button)
                      : actions->RemoveButton(button);
            CurrentButtons.removeOne(button);
        }
    }
}


void Game::on_Button_log_clicked()
{
    if(stackedWidgetMain->currentIndex()==0){
        ui->pushButton->setText("Закрыть");
        stackedWidgetMain->setCurrentIndex(1);
    }else{
        ui->pushButton->setText("Лог");
        stackedWidgetMain->setCurrentIndex(0);
    }
}

void Game::UpdateInit(INIT_TYPE type){
    switch (type)
    {
    case IT_DAYTIME:
        day++;
        night = false;
        ui->labelTime->setText("День "+QString::number(day));
        log->appendText("");
        log->appendText("День "+QString::number(day));
        break;
    case IT_NIGHTTIME:
        night = true;
        ui->labelTime->setText("Ночь "+QString::number(day));
        ui->labelEvent->setText("Ночные действия");
        log->appendText("");
        log->appendText("Ночь "+QString::number(day));
        break;
    }
}

void Game::UpdateEvents(QVector<EventInfo> events){
    foreach (EventInfo event, events) {
        switch (event.type)
        {
        case ET_DIED:
            foreach (QString man, event.message) {
                log->appendText(man+" обнаружен мертвым и был выкинут в космос");
            }
            break;
        case ET_UPPED:
            foreach (QString man, event.message) {
                log->appendText(man+" вышел из биованны");
            }
            break;
        case ET_DOWNED:
            foreach (QString man, event.message) {
                log->appendText(man+" из-за полученных ран помещен в биованну");
            }
            break;
        case ET_DUTIED:
            foreach (QString man, event.message) {
                log->appendText("Сегодня дежурит "+man);
            }
            break;
        case ET_MESSAGE:
            foreach (QString man, event.message) {
                log->appendText("Получено сообщение: "+man);
            }
            break;
        case ET_REMOVED_ROLE:
            log->appendText(event.message[0]+" потерял должность "+event.message[1]);
            break;
        case ET_SETTED_ROLE:
            log->appendText(event.message[0]+" получил должность "+event.message[1]);
            break;

        case ET_USED_ITEM:
        case ET_ULT_ITEM:
            log->appendText(event.message[0]);
            break;
        }
    }
}

void Game::UpdateItems(QMap<QString, int>& updated_items){

}

void Game::UpdateStat(CurrectPlayerInfo& info){

}

void Game::StartVoting(QString target, QStringList players){

}

void Game::UpdateVoting(QMap<QString, QPair<int, QString> > votelist){

}

void Game::EndVoting(QString target, QString name, QString result){

}

void Game::UpdatePlayers(QMap<QString, PlayerInfo>& updated_players){

}

void Game::PrepareTurn(){
    foreach (QPushButton* button, CurrentButtons) {
        button->setDisabled(true);
    }
    ui->pushButton->hide();
    ui->ButtonCancer->show();

    QObject* obj=QObject::sender();
    if (QPushButton *tb=qobject_cast<QPushButton *>(obj)){
        CurrentTurn = TurnObjectPool.key(tb);
        switch(CurrentTurn.type){
        case TT_ATTACK:
        case TT_INFECT:
        case TT_VOTE:
            foreach (PlayerWidget* player, playerlist->playlist.values()) {
                if(!CurrentTurn.targets.contains(player->name)){
                    player->setBackColor(player->palette().color(QPalette::Window).dark(150));
                }else{
                    connect(player,SIGNAL(mouseClick(PlayerWidget*)),this,SLOT(EndTurn(PlayerWidget*)));
                }
            }
            break;
        case TT_UP:
        case TT_DOWN:
        case TT_SKIP:
        case TT_UNVOTE:
            EndTurn();
            break;
        case TT_USE_ITEM:
            if(CurrentTurn.item == "Mop" ||
                    CurrentTurn.item == "Blaster" ||
                    CurrentTurn.item == "Scanner" ||
                    CurrentTurn.item == "Injector" ||
                    CurrentTurn.item == "Notebook" ||
                    CurrentTurn.item == "Badge"){
                foreach (PlayerWidget* player, playerlist->playlist.values()) {
                    if(!CurrentTurn.targets.contains(player->name)){
                        player->setBackColor(player->palette().color(QPalette::Window).dark(150));
                    }else{
                        connect(player,SIGNAL(mouseClick(PlayerWidget*)),this,SLOT(EndTurn(PlayerWidget*)));
                    }
                }
            }else if(CurrentTurn.item == "Battery"){
                if(night){
                    foreach (PlayerWidget* player, playerlist->playlist.values()) {
                        if(!CurrentTurn.targets.contains(player->name)){
                            player->setBackColor(player->palette().color(QPalette::Window).dark(150));
                        }else{
                            connect(player,SIGNAL(mouseClick(PlayerWidget*)),this,SLOT(EndTurn(PlayerWidget*)));
                        }
                    }
                }else{
                    targets->setLabel("Для использования доступны:","Зарядить");
                    targets->addWidgetBattery(CurrentTurn.targets);
                    connect(targets,SIGNAL(rotation(QStringList)),this,SLOT(EndTurn(QStringList)));
                    stackedWidgetMain->setCurrentIndex(2);
                }
            }
            else if(CurrentTurn.item == "Rotation"){
                targets->setLabel("Составление графика дежурств","Утвердить");
                targets->addWidgetRotation(CurrentTurn.targets);
                connect(targets,SIGNAL(rotation(QStringList)),this,SLOT(EndTurn(QStringList)));
                stackedWidgetMain->setCurrentIndex(2);
            }
            break;
        case TT_ULT_ITEM:
            if(CurrentTurn.item == "Battery"){
                targets->setLabel("Для починки доступны:","Починить");
                targets->addWidgetBattery(CurrentTurn.targets);
                connect(targets,SIGNAL(rotation(QStringList)),this,SLOT(EndTurn(QStringList)));
                stackedWidgetMain->setCurrentIndex(2);
            }else if(CurrentTurn.item == "Badge"){
                targets->setLabel("Для использования доступны:","Использовать");
                targets->addWidgetBattery(CurrentTurn.targets);
                connect(targets,SIGNAL(rotation(QStringList)),this,SLOT(EndTurn(QStringList)));
                stackedWidgetMain->setCurrentIndex(2);
            }
            else if(CurrentTurn.item == "Scanner" ||
                    CurrentTurn.item == "Injector" ||
                    CurrentTurn.item == "Notebook"){

            }
        }
    }
}

void Game::EndTurn(PlayerWidget* target){

    TurnObject send;
    send.type = CurrentTurn.type;
    send.item = CurrentTurn.item;
    send.targets.append(target->name);
    ALIENCLIENT.makeTurn(send);

    foreach (PlayerWidget* player, playerlist->playlist.values()) {
        if(!CurrentTurn.targets.contains(player->name)){
            player->setBackColor(player->palette().color(QPalette::Window).light(150));

        }else disconnect(player,SIGNAL(mouseClick(PlayerWidget*)),this,SLOT(EndTurn(PlayerWidget*)));
    }

    foreach (QPushButton* button, CurrentButtons) {
        button->setEnabled(true);
    }

    ui->pushButton->show();
    ui->ButtonCancer->hide();
}

void Game::EndTurn(){

    TurnObject send;
    send.type = CurrentTurn.type;

    ALIENCLIENT.makeTurn(send);


    foreach (QPushButton* button, CurrentButtons) {
        button->setEnabled(true);
    }

    ui->pushButton->show();
    ui->ButtonCancer->hide();
}

void Game::EndTurn(QStringList targetlist){

    TurnObject send;
    send.type = CurrentTurn.type;
    send.targets=targetlist;
    ALIENCLIENT.makeTurn(send);
    disconnect(targets,SIGNAL(rotation(QStringList)),this,SLOT(EndTurn(QStringList)));
    stackedWidgetMain->setCurrentIndex(0);
    foreach (QPushButton* button, CurrentButtons) {
        button->setEnabled(true);
    }

    ui->pushButton->show();
    ui->ButtonCancer->hide();
}


void Game::on_ButtonCancer_clicked()
{

}
