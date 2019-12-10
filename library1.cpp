//
// Created by Uriel on 10-Dec-19.
//

#include "DataStructure.h"
#include "list.h"
#include "Array.h"
#include "AVL.h"
#include "DataCenter&Server.h"
#include "library1.h"

void *Init() {
    DataStructure *DS = new DataStructure();
    return DS;
}

StatusType AddDataCenter(void *DS, int dataCenterID, int numOfServers) {
    return INVALID_INPUT;
}

StatusType RemoveDataCenter(void *DS, int dataCenterID) {
    return INVALID_INPUT;
}

StatusType RequestServer(void *DS, int dataCenterID, int serverID, int os,
                         int *assignedID) {
    if (DS == nullptr)
        return INVALID_INPUT;
    DataStructure *DC_manager = (DataStructure *) DS;
    DataCenter* DC = (*DC_manager).getDataCenter(dataCenterID);
    if (DC == nullptr)
        return FAILURE;
    Server *s = DC->getServer(serverID);
    if (s == nullptr)
        return INVALID_INPUT;
    if (s->ptrToFreeList() == nullptr)
        switch (os) {
            case 0: {
                assignedID = & DC->FreeLinuxList().GetHead()->GetValue()->ID();
                return (StatusType) DC->assignServer(
                        DC->FreeLinuxList().GetHead()->GetValue()->ID());
                }
            case 1: {
                assignedID = & DC->FreeWindowsList().GetHead()->GetValue()->ID();
                return (StatusType)DC->assignServer(
                        DC->FreeWindowsList().GetHead()->GetValue()->ID());
                }
            default:
                break;
        }
    else if (s->OS() != os){
        double old_linux_rank = DC->linuxAmount() + (1 / (DC->ID()));
        double old_win_rank = DC->linuxAmount() + (1 / (DC->ID()));
        DC->UpdateServerOs(s->ID());
        DC->assignServer(s->ID());
        DC_manager->RemoveRank(old_linux_rank, 0);
        DC_manager->RemoveRank(old_win_rank, 1);
        DC_manager->AddRank(DC->ID(), (DC->linuxAmount() + (1 / (DC->ID()))), 0);
        DC_manager->AddRank(DC->ID(), (DC->windowsAmont() + (1 / (DC->ID()))), 1);
    }
    else DC->assignServer(s->ID());

    return SUCCESS;
}

StatusType FreeServer(void *DS, int dataCenterID, int serverID) {
    if (DS == nullptr)
        return INVALID_INPUT;
    DataStructure *DC_manager = (DataStructure *) DS;
    DataCenter* DC = (*DC_manager).getDataCenter(dataCenterID);
    if (DC == nullptr)
        return FAILURE;
    Server *s = DC->getServer(serverID);
    if (s == nullptr)
        return INVALID_INPUT;
    else return (StatusType) DC->freeServer(s->ID());
}

GetDataCentersByOS(void *DS, int os, int **dataCenters, int *numOfDataCenters) {
    return INVALID_INPUT;
}

void Quit(void **DS) {
    *DS = nullptr;
}
