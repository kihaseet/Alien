#include "gametabs.h"

GameTabs::GameTabs()
{

}

void GameTabs::addTab(TabType id, GameTab tab)
{
    this->tabs.push_back(QPair<TabType, GameTab>(id, tab));
}

void GameTabs::addMainTabWidget(QLabel *mainTab, QLabel *mainTabInfo, QWidget* infoWidget)
{
    this->mainTab = mainTab;
    this->mainTabInfo = mainTabInfo;
    this->infoWidget = infoWidget;
}

void GameTabs::addSecTabWidget(QLabel *tab)
{
    this->secondaryTabs.push_back(tab);
}

void GameTabs::updateDay(QString day, QString info)
{
    for (QPair<TabType, GameTab>& tab: tabs)
    {
        if (tab.first == TAB_DAY)
        {
            tab.second.name = day;
            tab.second.addInfo = info;
        }
    }
}

TabType GameTabs::getActiveTab()
{
    return tabs[0].first;
}

void GameTabs::onClick(int tab_num)
{
    for (int ctab_num = tab_num; ctab_num < tabs.length(); ctab_num++)
    {
        QPair<TabType, GameTab> tab = tabs.last();
        tabs.pop_back();
        tabs.push_front(tab);
    }

    QPair<TabType, GameTab>& m_tab = tabs.first();

    mainTab->setText(m_tab.second.name);

    if (m_tab.first == TAB_DAY)
    {
        mainTabInfo->setText(m_tab.second.addInfo);
        infoWidget->setVisible(true);
    }
    else
    {
        infoWidget->setVisible(false);
    }

    for (int i = 1; i < tabs.length(); i++)
    {
        secondaryTabs[i - 1]->setText(tabs[i].second.name);
    }
}

