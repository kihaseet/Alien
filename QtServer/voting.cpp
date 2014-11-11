#include "voting.h"

voting::voting(QList <player> map,QString tar)
{
    target=tar;
    QListIterator<player>it(map);
    while (it.hasNext()){
        QMap <player,int> tmp=new QMap();
        tmp.insert(it.next(),0);
        votelist.insert(it.value(),tmp);
    }

}


bool voting::on_voting(player who,player whom){
    if(votelist.value(who).value(whom)==1){
        votelist.value(who).insert(whom,2);
    }else if((!votelist.value(who).contains(whom))||(votelist.value(who).value(whom)==0))
        {
            votelist.value(who).clear();
            votelist.value(who).insert(whom,1);
            QMutableMapIterator<player,QMap>it(votelist);
            while (it.hasNext()){
                QMutableMapIterator<player,int>jt(it.next());
                while (jt.hasNext()){
                    if (jt.next().value()==2){
                        jt.setValue(1);
                    }
                    }
                }
            }
    return is_complite();
}

bool voting::is_complite(){
   QMapIterator<player,QMap>it(votelist);
   while (it.hasNext()){
       QMapIterator<player,int>jt(it.next());
       while (jt.hasNext()){
           if(jt.next().value()!=2){
               return false;
           }
       }
   }
   return true;
}
