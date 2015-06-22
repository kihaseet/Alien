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
    status->setGeometry((this->width() + status->width())/2, (this->height() + status->height())/2, status->width(), status->height());
    status->hide();
    playerlist = new PlayerList(this);
    qDebug() << playerlist->width() << " : " << playerlist->height() << endl;
    targets = new Targets(this);

    stackedWidgetInventory = new QStackedWidget(this);
    stackedWidgetInventory->addWidget(actions);
    stackedWidgetInventory->addWidget(inventory);
    ui->LayoutActions->addWidget(stackedWidgetInventory);
    stackedWidgetInventory->setCurrentIndex(0);

    stackedWidgetMain = ui->stackedWidgetMain;
    stackedWidgetMain->addWidget(playerlist);
    stackedWidgetMain->addWidget(log);
    stackedWidgetMain->addWidget(targets);
    //ui->LayoutPlayerList->addWidget(stackedWidgetMain);
    stackedWidgetMain->setCurrentIndex(0);
}

void Game::StartGame( QMap<QString, PlayerInfo> play){
    if (play.size() == 0)
    {
        return;
    }
    playerlist->startGame(play);
}

Game::~Game()
{
    delete ui;
}

void Game::updateCurrentTurn(TURN_TYPE type)
{
    updateCurrentTurn(type, CurrentTurn.targets, CurrentTurn.item);
}

void Game::updateCurrentTurn(TURN_TYPE type, QStringList targets, QString item)
{
    QString actionString;
    CurrentTurn.type = type;
    CurrentTurn.item = item;
    CurrentTurn.targets = targets;

    switch(CurrentTurn.type)
    {
    case TT_ULT_ITEM:
        actionString = "Ультовать предметом";
        break;
    case TT_USE_ITEM:
        actionString = "Использовать предмет";
        break;
    case TT_ATTACK:
        actionString = "Напасть";
        break;
    case TT_INFECT:
        actionString = "Заразить";
        break;
    case TT_UP:
        actionString = "Выйти из ванны" ;
        break;
    case TT_DOWN:
        actionString = "Лечь в ванну";
        break;
    case TT_SKIP:
        actionString = "Ждать" ;
        break;
    case TT_VOTE:
        actionString = "Голосовать" ;
        break;
    case TT_UNVOTE:
        actionString = "Снять голос" ;
        break;
    }

    if (CurrentTurn.item.length() != 0)
    {
        actionString += " [" + CurrentTurn.item + "]";
    }

    this->ui->lblCurrentAction->setText(actionString);
}

void Game::on_pushButton_clicked()
{
    if (CurrentTurn.type == TT_USE_ITEM || CurrentTurn.type == TT_ULT_ITEM)
    {
        if (ui->pushButton->text() == "Отмена")
        {
            ui->pushButton->setText("Закрыть");
            foreach (QPushButton* button, CurrentButtons) {
                button->setDisabled(false);
            }
            updateCurrentTurn(PreUseTurn.type, PreUseTurn.targets, PreUseTurn.item);
            //CurrentTurn = PreUseTurn;
            foreach (PlayerWidget* player, playerlist->playlist.values()) {
                if(!CurrentTurn.targets.contains(player->name)){
                    player->setBackColor(player->palette().color(QPalette::Window).dark(150));
                }else{
                    connect(player,SIGNAL(mouseClick(PlayerWidget*)),this,SLOT(EndTurn(PlayerWidget*)));
                }
            }
        }
        else
        {
            ui->pushButton->setText("Отмена");
        }
    }
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
        else if(var.type==TT_VOTE){
            foreach (PlayerWidget* player, playerlist->playlist.values()) {
                player->setDisabled(!var.targets.contains(player->name));
            }
        }
        else if(var.type==TT_UNVOTE){
            foreach (PlayerWidget* player, playerlist->playlist.values()) {
                player->setDisabled(!var.targets.contains(player->name));
            }
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
        ui->Button_log->setText("Закрыть");
        stackedWidgetMain->setCurrentIndex(1);
    }else{
        ui->Button_log->setText("Лог");
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
    qDebug() << "STUB: UpdateItems";
}

void Game::UpdateStat(CurrectPlayerInfo& info){
    status->updateStatus(info);
    qDebug() << "UpdateStat";
}

void Game::StartVoting(QString target, QStringList players){
    updateCurrentTurn(TT_VOTE);
    //CurrentTurn.type = TT_VOTE;
    CurrentTurn.targets.clear();
    CurrentTurn.targets.append(players);
    currentVoting.clear();
    this->ui->labelEvent->setText("Голосование на " + target);
    foreach (PlayerWidget* player, playerlist->playlist.values()) {
        currentVoting[player->name] = "";
        if(!CurrentTurn.targets.contains(player->name)){
            player->setBackColor(player->palette().color(QPalette::Window).dark(150));
        }else{
            connect(player,SIGNAL(mouseClick(PlayerWidget*)),this,SLOT(EndTurn(PlayerWidget*)));
        }
    }

    log->appendText("Начато голосование на " + target);

    qDebug() << "StartVoting";
}

void Game::UpdateVoting(QMap<QString, QPair<int, QString> > votelist){
    QMap<QString, int> current_votes;

    QString last_target = "";

    foreach(QString who, votelist.keys())
    {
        if (votelist[who].first == 1)
        {
            if (currentVoting[who] != votelist[who].second)
            {
                currentVoting[who] = votelist[who].second;
                log->appendText(who + " проголосовал за " + votelist[who].second);
            }
            current_votes[votelist[who].second] += 1;
            if (who == ALIENCLIENT.getCurrentPlayer().name)
            {
                last_target = votelist[who].second;
            }
        }
        else
        {
            if (currentVoting[who] == votelist[who].second)
            {
                currentVoting[who] = "";
                log->appendText(who + " снял голос за " + votelist[who].second);
            }
            current_votes[votelist[who].second] += 0;
        }
    }

    updateCurrentTurn(last_target.length() > 0 ? TT_UNVOTE : TT_VOTE);
    //CurrentTurn.type = last_target.length() > 0 ? TT_UNVOTE : TT_VOTE;

    foreach (PlayerWidget* player, playerlist->playlist.values()) {
        player->setVote(current_votes[player->name]);
        if (last_target.length() != 0)
        {
            player->setDisabled(!(player->name == last_target));
        }
        else
        {
            player->setDisabled(false);
        }
    }

    qDebug() << "UpdateVoting";
}

void Game::EndVoting(QString target, QString name, QString result){
    qDebug() << "EndVoting";
    log->appendText("Результаты голосования на " + target + ": " + name + " - " + result);
    updateCurrentTurn(TT_NOTHING);
    //CurrentTurn.type = TT_NOTHING;
    foreach (PlayerWidget* player, playerlist->playlist.values())
    {
        player->setDisabled(false);
    }

}

void Game::UpdatePlayers(QMap<QString, PlayerInfo>& updated_players){
    this->playerlist->startGame(updated_players);
}

void Game::PrepareTurn(){
    PreUseTurn = CurrentTurn;
    foreach (QPushButton* button, CurrentButtons) {
        button->setDisabled(true);
    }

    QObject* obj=QObject::sender();
    if (QPushButton *tb=qobject_cast<QPushButton *>(obj)){
        updateCurrentTurn(TurnObjectPool.key(tb).type, TurnObjectPool.key(tb).targets, TurnObjectPool.key(tb).item);
        //CurrentTurn = TurnObjectPool.key(tb);
        qDebug() << "PrepareTurn: " << CurrentTurn.item;
        qDebug() << "PrepareTurn: " << CurrentTurn.type;
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
            this->ui->pushButton->setText("Отмена");

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
            this->ui->pushButton->setText("Отмена");
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

//    foreach (PlayerWidget* player, playerlist->playlist.values()) {
//        if(!CurrentTurn.targets.contains(player->name)){
//            player->setBackColor(player->palette().color(QPalette::Window).light(150));

//        }else disconnect(player,SIGNAL(mouseClick(PlayerWidget*)),this,SLOT(EndTurn(PlayerWidget*)));
//    }

    foreach (QPushButton* button, CurrentButtons) {
        button->setEnabled(true);
    }
}

void Game::EndTurn(){

    TurnObject send;
    send.type = CurrentTurn.type;

    qDebug() << "EndTurn: Calling makeTurn with send.type == " << send.type;

    ALIENCLIENT.makeTurn(send);


    foreach (QPushButton* button, CurrentButtons) {
        button->setEnabled(true);
    }
}

void Game::EndTurn(QStringList targetlist){

    TurnObject send;
    send.type = CurrentTurn.type;
    send.item = CurrentTurn.item;
    send.targets=targetlist;
    ALIENCLIENT.makeTurn(send);
    disconnect(targets,SIGNAL(rotation(QStringList)),this,SLOT(EndTurn(QStringList)));
    stackedWidgetMain->setCurrentIndex(0);
    foreach (QPushButton* button, CurrentButtons) {
        button->setEnabled(true);
    }
}

void Game::on_Button_Status_clicked()
{
    if (status->isHidden())
    {
        status->show();
        stackedWidgetInventory->hide();
        stackedWidgetMain->hide();
    }
    else
    {
        status->hide();
        stackedWidgetInventory->show();
        stackedWidgetMain->show();
    }
}
