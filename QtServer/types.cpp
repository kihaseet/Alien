#include "types.h"

QMap<QString, ROLE> RegisterObject::initColumn()
{
    QMap<QString, ROLE> map;
    map.insert("alien",         RT_ALIEN);
    map.insert("Passenger",     RT_PASSENGER);
    map.insert("Captain",       RT_CAPTAIN);
    map.insert("Assistant",     RT_ASSISTANT);
    map.insert("Gunmen",        RT_GUNMEN);
    map.insert("Scientist",     RT_SCIENTIST);
    map.insert("Signalmen",     RT_SIGNALMEN);
    map.insert("Doctor",        RT_DOCTOR);
    map.insert("Signalmen",     RT_SIGNALMEN);
    map.insert("Engineer",      RT_ENGINEER);
    map.insert("Dep_Gunmen",    RT_DEP_GUNMEN);
    map.insert("Dep_Doctor",    RT_DEP_DOCTOR);
    map.insert("Dep_Scientist", RT_DEP_SCIENTIST);
    map.insert("Dep_Signalmen", RT_DEP_SIGNALMEN);
    map.insert("Dep_Engineer",  RT_DEP_ENGINEER);
    return map;
}

QMap <QString, ROLE> RegisterObject::RoleDescr = initColumn();

