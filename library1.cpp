//
// Created by Uriel on 10-Dec-19.
//

#include "DataStructure.h"
#include "list.h"
#include "Array.h"
#include "AVL.h"
#include "DataCenter&Server.h"
#include "DataStructure.cpp"
#include "list.cpp"
#include "Array.cpp"
#include "AVL.cpp"
#include "DataCenter&Server.cpp"
#include "library1.h"

void *Init() {
    DataStructure *DS = new DataStructure();
    return DS;
}

void FillArray(int** dataCenters, int* counter, AVLNode<double>* root);

StatusType AddDataCenter(void *DS, int dataCenterID, int numOfServers) {
    if (DS == NULL || dataCenterID < 1 || numOfServers < 1)
        return INVALID_INPUT;
    DataStructure* ds = (DataStructure*)DS;
    if (ds->getDataCenter(dataCenterID)) //if the ID alredy exist in the system
        return FAILURE;
    DataCenter data_center(dataCenterID, numOfServers);
    //if (&data_center == NULL)  //testing memory alocations of servers
    StatusTypeDS output_ds;
    output_ds = ds->AddDataCenter(data_center, dataCenterID);
    if (output_ds != SUCCESS_DC)
        return (StatusType)output_ds;
    double linux_key = data_center.linuxAmount() + (1 - 1 / dataCenterID);
    double windows_key = data_center.windowsAmont() + (1 - 1 / dataCenterID);
    output_ds = ds->AddRank(dataCenterID, linux_key, 0);
    if (output_ds != SUCCESS_DC)
        return (StatusType)output_ds;
    output_ds = ds->AddRank(dataCenterID, windows_key, 1);
    if (output_ds != SUCCESS_DC)
        return (StatusType)output_ds;
    return SUCCESS;
}

StatusType RemoveDataCenter(void *DS, int dataCenterID) {
    if (DS == NULL || dataCenterID < 1)
        return INVALID_INPUT;
    DataStructure* ds = (DataStructure*)DS;
    DataCenter* data_center = ds->getDataCenter(dataCenterID);
    if (data_center == NULL)
        return FAILURE;
    StatusTypeDS output_ds;
    output_ds = ds->RemoveDataCenter(dataCenterID);
    if (output_ds != SUCCESS_DC)
        return (StatusType)output_ds;
    double linux_key = data_center->linuxAmount() + (1 - 1 / dataCenterID);
    double windows_key = data_center->windowsAmont() + (1 - 1 / dataCenterID);
    output_ds = ds->RemoveRank(linux_key, 0);
    if (output_ds != SUCCESS_DC)
        return (StatusType)output_ds;
    output_ds = ds->RemoveRank(windows_key, 1);
    if (output_ds != SUCCESS_DC)
        return (StatusType)output_ds;
    return SUCCESS;
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

StatusType GetDataCentersByOS(void *DS, int os, int **dataCenters, int* numOfDataCenters) {
    if (DS == NULL || dataCenters == NULL || numOfDataCenters == NULL || os < 0 || os > 1)
        return INVALID_INPUT;

    DataStructure* ds = (DataStructure*)DS;
    int num_of_servers = ds->NumOfDataCenters();
    *numOfDataCenters = ds->NumOfDataCenters();
    if (*numOfDataCenters == 0)
        return FAILURE;
    *dataCenters = (int *) malloc(num_of_servers * sizeof(int));
    //preordar traversal on an avl tree
    AVLNode<double>* root = ds->GetRootByOs(os);
    int counter = 0;
    FillArray(dataCenters,&counter, root);
    return SUCCESS;
}

void FillArray(int** dataCenters, int* conter , AVLNode<double>* root) {
    if (root != NULL)
    {
        FillArray(dataCenters, conter, root->left);
        (*dataCenters)[*conter] = root->data;
        (*conter)++;
        FillArray(dataCenters, conter, root->right);
    }
}

void Quit(void **DS) {
    *DS = nullptr;
}
