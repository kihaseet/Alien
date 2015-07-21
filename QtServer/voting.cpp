#include "voting.h"

voting::voting(){
    //qDebug()<<"voting::voting()";
    is_over = true;
}

voting::voting(QList<QString> mapwhom, ROLE tar)
//создает новое голосование, задавая цель, получая список всех голосующих и список против кого голосуют
{
    //qDebug()<<"voting::voting(QList<QString> mapwho, QList<QString> mapwhom, QString tar)"<<tar;
    target = tar;
    electlist.clear();
    votelist.clear();
    winners.clear();
    electlist.append(mapwhom);
    is_over = false;
    noteName = "";
}

void voting::send_voting_over(QList<QString> v){
    emit voting_over(v);
}


void voting::on_voting(QString who, QString whom){
    qDebug()<<"void voting::on_voting(QString who, QString whom)";
    if(electlist.contains(whom))
    {
        foreach (VoteObject* vote, votelist)
        {
            if(vote->who == who && vote->status == 0)
            {
                    vote->whom = whom;
                    vote->status = 1;
                    break;
            }
        }
    }
    if(is_complite())
    {
        calc_votes();
        emit voting_over(winners);
    }
}

void voting::off_voting(QString who){

    foreach (VoteObject* vote, votelist)
    {
        if(vote->who == who && vote->status == 1)
        {
            vote->status = 0;
            break;
        }
    }
    //тут будет отправка сообщения всем о снятии голоса
}

bool voting::is_vote(QString who)
{
    foreach (VoteObject* vote, votelist) {
        if(vote->who == who)
        {
            if(vote->status == 1)
                return true;
            else return false;
        }
    }
    return false;
}

bool voting::is_complite()
{
    foreach (VoteObject* tmp, votelist)
    {
        if(tmp->status == 0)
            return false;
    }
    return true;
}

void voting::calc_votes(){
    qDebug()<<"voting::calc_votes()";
    winners.clear();

    QMap <QString,int> result;
    foreach (VoteObject* var, votelist)
    {
        int i = result.value(var->whom,-1);
        result.insert(var->whom, i + 1);
    }
    if(electlist.contains(noteName))
    {
        ++result[noteName];
    }

    int i = 0;
    foreach (QString name, result.keys())
    {
        if(result[name] > i)
        {
            winners.clear();
            winners.append(name);
            i = result[name];
        }else if(result[name] == i){
            winners.append(name);
        }
    }
}

void voting::use_notebook(QString whom){
    noteName = whom;
}

void voting::ult_notebook()
{
    emit voting_canseled();
}
