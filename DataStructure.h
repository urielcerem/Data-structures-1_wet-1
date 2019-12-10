//
// Created by Uriel on 10-Dec-19.
//

#ifndef WET_1_DATASTRUCTURE_H
#define WET_1_DATASTRUCTURE_H

#include "list.h"
#include "Array.h"
#include "AVL.h"
#include "DataCenter&Server.h"

typedef enum {
    SUCCESS_DS = 0,
    FAILURE_DS = -1,
    ALLOCATION_ERROR_DS = -2,
    INVALID_INPUT_DS = -3
} StatusTypeDS;

class DataStructure{
    AVLTree <DataCenter> data_centers_tree;
    AVLTree <double> ranked_by_linux;
    AVLTree <double> ranked_by_windows;
    int num_of_data_centers;

public:
    DataStructure() = default;
    ~DataStructure() = default;
    DataStructure(const DataStructure & DS) = default;
    StatusTypeDS AddDataCenter (DataCenter DS, double key);
    StatusTypeDS AddRank(int data_centerID, double key, int OS);
    StatusTypeDS RemoveDataCenter (double key);
    StatusTypeDS RemoveRank(double key, int OS);
    DataCenter *  getDataCenter(double key);
    double getRankedID(double key, int OS);
	int NumOfDataCenters();
	AVLNode<double>* GetRootByOs(int os);
};

#endif //WET_1_DATASTRUCTURE_H
