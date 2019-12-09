//
// Created by Uriel on 10-Dec-19.
//

#ifndef WET_1_DATASTRUCTURE_H
#define WET_1_DATASTRUCTURE_H

#include "list.h"
#include "Array.h"
#include "AVL.h"
#include "DataCenter&Server.h"

class DataStructure{
    AVLTree <DataCenter> data_centers_tree;
    AVLTree <double> ranked_by_linux;
    AVLTree <double> ranked_by_windows;
    int num_of_data_centers;

public:
    DataStructure();
    ~DataStructure();
    DataStructure(const DataStructure & DS);
    

};

#endif //WET_1_DATASTRUCTURE_H
