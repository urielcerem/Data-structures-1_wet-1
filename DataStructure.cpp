//
// Created by Uriel on 10-Dec-19.
//

#include "DataStructure.h"
#include "list.h"
#include "Array.h"
#include "AVL.h"
#include "DataCenter&Server.h"

StatusTypeDS DataStructure::AddDataCenter(DataCenter DS, double key) {
    data_centers_tree.Insert(DS, key);
    ++num_of_data_centers;
    return SUCCESS_DS;
}

StatusTypeDS DataStructure::AddRank(int data_centerID, double key, int OS) {
    switch (OS) {
        case 0:{
            ranked_by_linux.Insert(data_centerID, key);
            return SUCCESS_DS;
        }
        case 1: {
            ranked_by_windows.Insert(data_centerID,key);
            return SUCCESS_DS;
        }
        default:
            break;
    }
    return INVALID_INPUT_DS;
}

StatusTypeDS DataStructure::RemoveDataCenter(double key) {
    if (getDataCenter(key) == nullptr)
        return FAILURE_DS;
    data_centers_tree.Delete(key);
    --num_of_data_centers;
    return SUCCESS_DS;
}

StatusTypeDS DataStructure::RemoveRank(double key, int OS) {
    if (getRankedID(key, OS) == 0)
        return FAILURE_DS;
    if (OS == 1)
        ranked_by_windows.Delete(key);
    else ranked_by_linux.Delete(key);
    return SUCCESS_DS;
}

DataCenter *DataStructure::getDataCenter(double key) {
    return data_centers_tree.Find(key);
}

double DataStructure::getRankedID(double key, int OS) {
    if (OS == 1)
        return *ranked_by_windows.Find(key);
    else if (OS == 0)
        return *ranked_by_linux.Find(key);
    return 0;
}

int DataStructure::NumOfDataCenters() {
	return num_of_data_centers;
}

AVLNode<double>* DataStructure::GetRootByOs(int os) {
	switch (os) {
	case 0:
		return ranked_by_linux.root;
	case 1:
		return ranked_by_windows.root;
	default:
		return NULL;
	}
}