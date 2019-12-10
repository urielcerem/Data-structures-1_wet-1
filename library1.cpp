#include "Array.h"
#include "AVL.h"
#include "list.h"
#include "DataStructure.h"
#include "library1.h"

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
		(*dataCenters)[*conter] = root->key;
		(*conter)++;
		FillArray(dataCenters, conter, root->right);
	}
}
