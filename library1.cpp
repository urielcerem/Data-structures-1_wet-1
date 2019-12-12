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

void FillArray(int** dataCenters, int* counter, AVLNode<double>* root);

void dubugPrinting(DataStructure* ds) {
	std::cout << "data_centers :" << std::endl;
	ds->data_centers_tree.PrintInOrder();
	std::cout << "data centers root = " << ds->data_centers_tree.root->data.ID() << std::endl;
	std::cout << "linux rank:" << std::endl;
	ds->ranked_by_linux.PrintInOrder();
	std::cout << "linux rank root = " << ds->ranked_by_linux.root->data << std::endl;
	std::cout << "windows rank" << std::endl;
	ds->ranked_by_windows.PrintInOrder();
	std::cout << "windows rank root = " << ds->ranked_by_windows.root->data << std::endl;
}

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
	if (output_ds != SUCCESS_DS)
		return (StatusType)output_ds;
	double linux_key = data_center.linuxAmount() + (1.0 / dataCenterID);
	double windows_key = data_center.windowsAmont() + (1.0 / dataCenterID);
	output_ds = ds->AddRank(dataCenterID, linux_key, 0);
	if (output_ds != SUCCESS_DS)
		return (StatusType)output_ds;
	output_ds = ds->AddRank(dataCenterID, windows_key, 1);
	if (output_ds != SUCCESS_DS)
		return (StatusType)output_ds;

	//dubugPrinting(ds);

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
	double linux_key = data_center->linuxAmount() + (1.0 / dataCenterID);
	double windows_key = data_center->windowsAmont() + (1.0 / dataCenterID);
	//std:cout << linux_key << std::endl;
	//std:cout << windows_key << std::endl;
	output_ds = ds->RemoveRank(linux_key, 0);
	if (output_ds != SUCCESS_DS)
		return (StatusType)output_ds;
	output_ds = ds->RemoveRank(windows_key, 1);
	if (output_ds != SUCCESS_DS)
		return (StatusType)output_ds;
	output_ds = ds->RemoveDataCenter(dataCenterID);
	if (output_ds != SUCCESS_DS)
		return (StatusType)output_ds;

	//dubugPrinting(ds);

	return SUCCESS;
}

StatusType RequestServer(void *DS, int dataCenterID, int serverID, int os,
	int *assignedID) {
	if (DS == nullptr || dataCenterID < 1 || serverID < 0 || os < 0 || os > 1 || assignedID == NULL)
		return INVALID_INPUT;
	DataStructure *DC_manager = (DataStructure *)DS;
	DataCenter* DC = (*DC_manager).getDataCenter(dataCenterID);
	if (DC == nullptr)
		return FAILURE;
	if (serverID > DC->serversAmount())
		return INVALID_INPUT;
	Server *s = DC->getServer(serverID);
	if (s == nullptr)
		return INVALID_INPUT;
	if (s->ptrToFreeList() == nullptr)
	{
		switch (os) {
		case 0: {
			if (DC->FreeLinuxList().GetHead() != NULL)
			{
				*assignedID = DC->FreeLinuxList().GetHead()->data.ID();
				//std::cout << *assignedID << std::endl;
				return (StatusType)DC->assignServer(*assignedID);
			}
			else if (DC->FreeWindowsList().GetHead() != NULL)
			{
				*assignedID = DC->FreeWindowsList().GetHead()->data.ID();
				return (StatusType)DC->assignServer(*assignedID);
			}
			else
				return FAILURE;
		}
		case 1: {
			if (DC->FreeWindowsList().GetHead() != NULL)
			{
				*assignedID = DC->FreeWindowsList().GetHead()->data.id;
				return (StatusType)DC->assignServer(*assignedID);
			}
			else if (DC->FreeLinuxList().GetHead() != NULL)
			{
				*assignedID = DC->FreeLinuxList().GetHead()->data.ID();
				//std::cout << *assignedID << std::endl;
				return (StatusType)DC->assignServer(*assignedID);
			}
			else
				return FAILURE;
		}
		default:
			break;
		}
	}
	else if (s->OS() != os) {
		double old_linux_rank = DC->linuxAmount() + (1.0 / (DC->ID()));
		double old_win_rank = DC->windowsAmont() + (1.0 / (DC->ID()));
		//std::cout << "old_linux_rank = " << old_linux_rank << std::endl;
		//std::cout << "old_win_rank = " << old_win_rank << std::endl;
		DC_manager->RemoveRank(old_linux_rank, 0);
		DC_manager->RemoveRank(old_win_rank, 1);
		DC->UpdateServerOs(s->ID());
		DC->assignServer(s->ID());
		double new_linux_rank = DC->linuxAmount() + (1.0 / (DC->ID()));
		double new_win_rank = DC->windowsAmont() + (1.0 / (DC->ID()));
		//std::cout << "new_linux_rank = " << new_linux_rank << std::endl;
		//std::cout << "new_win_rank = " << new_win_rank << std::endl;
		DC_manager->AddRank(DC->ID(), new_linux_rank, 0);
		DC_manager->AddRank(DC->ID(), new_win_rank, 1);
		*assignedID = serverID;
	}
	else {
		DC->assignServer(s->ID());
		*assignedID = serverID;
	}

	//dubugPrinting(DC_manager);

	return SUCCESS;
}

StatusType FreeServer(void *DS, int dataCenterID, int serverID) {
	if (DS == nullptr || dataCenterID < 1 || serverID < 1)
		return INVALID_INPUT;
	DataStructure *DC_manager = (DataStructure *)DS;
	DataCenter* DC = (*DC_manager).getDataCenter(dataCenterID);
	if (DC == nullptr)
		return FAILURE;
	if (serverID > DC->serversAmount())
		return INVALID_INPUT;
	Server *s = DC->getServer(serverID);
	if (s == nullptr)
		return INVALID_INPUT;
	if (s->ptrToFreeList() != NULL)
		return FAILURE;
	else return (StatusType)DC->freeServer(s->ID());
}

StatusType GetDataCentersByOS(void *DS, int os, int **dataCenters, int* numOfDataCenters) {
	if (DS == NULL || dataCenters == NULL || numOfDataCenters == NULL || os < 0 || os > 1)
		return INVALID_INPUT;

	DataStructure* ds = (DataStructure*)DS;
	int num_of_servers = ds->NumOfDataCenters();
	*numOfDataCenters = ds->NumOfDataCenters();
	if (*numOfDataCenters == 0)
		return FAILURE;
	*dataCenters = (int *)malloc(num_of_servers * sizeof(int));
	//preordar traversal on an avl tree
	AVLNode<double>* root = ds->GetRootByOs(os);
	int counter = num_of_servers - 1;
	FillArray(dataCenters, &counter, root);
	return SUCCESS;
}

void FillArray(int** dataCenters, int* counter, AVLNode<double>* root) {
	if (root != NULL)
	{
		FillArray(dataCenters, counter, root->left);
		if (*counter > -1)
		{
		(*dataCenters)[*counter] = root->data;
		(*counter)--;
		}
		FillArray(dataCenters, counter, root->right);
	}
}

void Quit(void **DS) {
    delete (DataStructure*) *DS;
	*DS = nullptr;
}