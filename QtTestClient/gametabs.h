#ifndef GAMETABS_H
#define GAMETABS_H

#include <QPair>
#include <QString>
#include <QLabel>
#include <QWidget>
#include <QQueue>

enum TabType
{
    TAB_DAY = 0,
    TAB_PROFILE = 1,
    TAB_LOG = 2
};

struct GameTab
{
    QString name;
    QString addInfo;

    GameTab()
    {
        name = "";
        addInfo = "";
    }

    GameTab(QString name, QString addInfo)
    {
        this->name = name;
        this->addInfo = addInfo;
    }
};

class GameTabs
{
    QQueue<QPair<TabType, GameTab>> tabs;

    QLabel* mainTab;
    QLabel* mainTabInfo;
    QWidget* infoWidget;

    QQueue<QLabel*> secondaryTabs;

public:
    GameTabs();
    void addTab(TabType id, GameTab tab);
    void addMainTabWidget(QLabel* mainTab, QLabel* mainTabInfo, QWidget* infoWidget);
    void addSecTabWidget(QLabel* tab);
    void updateDay(QString day);
    void updateDayInfo(QString info);
    TabType getActiveTab();
    void onClick(int tab_num);
};

#endif // GAMETABS_H
