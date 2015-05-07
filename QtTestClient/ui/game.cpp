#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    day=0;

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
            case TT_VOTE:
                txt = "Голосовать" ;
                break;
            case TT_UNVOTE:
                txt = "Снять голос";
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
        ui->labelTime->setText("День "+QString::number(day));
        log->appendText("");
        log->appendText("День "+QString::number(day));
        break;
    case IT_NIGHTTIME:
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
    QObject* obj=QObject::sender();
    TurnObject tmp;
    if (QPushButton *tb=qobject_cast<QPushButton *>(obj))
        tmp = TurnObjectPool.key(tb);
    switch(tmp.type){
    case TT_ATTACK:
        foreach (QString name, tmp.targets) {

        }
    }
}
