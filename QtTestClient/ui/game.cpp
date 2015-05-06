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

    stackedWidgetInventory = new QStackedWidget(this);
    stackedWidgetInventory->addWidget(actions);
    stackedWidgetInventory->addWidget(inventory);
    ui->LayoutActions->addWidget(stackedWidgetInventory);
    stackedWidgetInventory->setCurrentIndex(0);

    stackedWidgetMain = new QStackedWidget(this);
    stackedWidgetMain->addWidget(playerlist);
    stackedWidgetMain->addWidget(log);
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
        int index = TurnObjectPool.indexOf(var);
        if(index!=-1){
            TurnObjectPool[index].targets=var.targets;
        }
        else{
            TurnObjectPool.append(var);
            index = TurnObjectPool.indexOf(var);

            TurnObjectPool[index].button = new QPushButton(this);
            if(var.type==TT_USE_ITEM || var.type==TT_ULT_ITEM){
                (var.type==TT_USE_ITEM) ?
                            TurnObjectPool[index].button->setText(var.item)
                          : TurnObjectPool[index].button->setText("U"+var.item);

            }else{
                QString txt;
                switch (var.type)
                {
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
                TurnObjectPool[index].button->setText(txt);
            }

            TurnObjectPool[index].curr=false;
           // connect(TurnObjectPool[index].button,SIGNAL(clicked()),TurnObjectPool[index],SLOT);
        }


        if(!TurnObjectPool[index].curr){
            (var.type==TT_USE_ITEM || var.type==TT_ULT_ITEM) ?
                        inventory->AddButton(TurnObjectPool[index].button)
                      : actions->AddButton(TurnObjectPool[index].button);
            TurnObjectPool[index].curr=true;
        }
    }

    foreach (TurnObject var, TurnObjectPool) {
        if(var.curr && !ActionsVector.contains(var)){
            (var.type==TT_USE_ITEM || var.type==TT_ULT_ITEM) ?
                        inventory->RemoveButton(var.button)
                      : actions->RemoveButton(var.button);

            var.curr=false;
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

void Game::MakeTurn(){
    //TurnObjectPool.(QPushButton)sender
}
