#include "voting.h"

voting::voting(){
    qDebug()<<"voting::voting()";
    is_over=true;
}

voting::voting(QList<QString> mapwho, QList<QString> mapwhom, QString tar)
//создает новое голосование, задавая цель, получая список всех голосующих и список против кого голосуют
{
    qDebug()<<"voting::voting(QList<QString> mapwho, QList<QString> mapwhom, QString tar)"<<tar;
    target=tar;
    electlist.clear();
    this->votelist.clear();
    winners.clear();
    this->electlist.append(mapwhom);
    is_over=false;

    //    QListIterator<QString>it(mapwho);
    //    while (it.hasNext()){
    //        QPair <QString,int> tmp;
    //        tmp.first=it.next();
    //        tmp.second=0;
    //        votelist.insert(it.value(),tmp);
    //    }
    foreach (QString var, mapwho) {
        QPair <QString,int> tmp;
        tmp.first=var;
        tmp.second=0;
        this->votelist.insert(var,tmp);
    }
}


void voting::on_voting(QString who, QString whom){
    qDebug()<<"void voting::on_voting(QString who, QString whom)";
    if(electlist.contains(whom) && this->votelist.contains(who)){
        if(this->votelist.value(who).second==0){
            QPair <QString,int> tmp;
            tmp.first=whom;
            tmp.second=1;
            this->votelist.insert(who,tmp);
        }
        //тут будет отправка всем сообщения об изменении голоса
    }
    if(is_complite()){
        calc_votes();
        emit voting_over(winners);
    }
}

void voting::off_voting(QString who){
    qDebug()<<"void voting::off_voting(QString who)";
    if(votelist.contains(who) && votelist.value(who).second==1){
        QPair <QString,int> tmp;
        tmp.first=votelist.value(who).first;
        tmp.second=0;
        votelist.insert(who,tmp);
    }
    //тут будет отправка сообщения всем о снятии голоса
}

bool voting::is_complite(){
    qDebug()<<"voting::is_complite()";
    QPair <QString,int> tmp;
    foreach (tmp, this->votelist.values()) {
        if(tmp.second==0)
            return false;
    }
    return true;
}

void voting::calc_votes(){
    qDebug()<<"voting::calc_votes()";
    //    QMap <QString,int> calc;
    //    foreach (QString var, electlist) {
    //        calc.insert(var,0);
    //    }
    //    QPair <QString,int> tmp;
    //    foreach (tmp, votelist.values()) {
    //        if(electlist.contains(tmp.first)){
    //            calc.insert(tmp.first,calc.value(tmp.first)+1);
    //        }
    //  }
    winners.clear();
    QList<QPair<QString,int> > result;
    foreach (QString var, electlist) {
        result.append(qMakePair(var,0));
    }
    QPair <QString,int> tmp;
    foreach (tmp, votelist.values()) {
        if(electlist.contains(tmp.first)){
            //calc.insert(tmp.first,calc.value(tmp.first)+1);
            QPair <QString,int> ttmp;
            foreach (ttmp, result) {
                if(ttmp.first==tmp.first){
                    result.append(qMakePair(ttmp.first,ttmp.second+1));
                    result.removeOne(ttmp);

                }
            }
        }
    }

//    foreach (QString v, calc.keys()) {
//        result.append(qMakePair(v,calc.value(v)));
//    }
    qSort(result.begin(),result.end(),QPairSecondComparer());

    QPair<QString,int> v1;
    foreach (v1, result) {
        if(v1.second<result.first().second)
            result.removeOne(v1);
    }
    QPair<QString,int> var;
    foreach (var, result) {
        winners.append(var.first);
    };
}

void voting::use_notebook(QString who,QString whom,QString useit){
    if (useit=="Notebook"){
        votelist.insert("",qMakePair(whom,1));
    }
}

void voting::ult_notebook(QString who,QString whom,QString useit){
    if(useit=="Notebook"){
        emit voting_canseled();
    }
}
