//
// Created by Uriel on 04-Dec-19.
//
#include "Array.h"
#include "list.h"

#ifndef WET_1_DATACENTER_SERVER_H
#define WET_1_DATACENTER_SERVER_H

typedef enum {
    SUCCESS = 0,
    FAILURE = -1,
    ALLOCATION_ERROR = -2,
    INVALID_INPUT = -3
} StatusType;

class Server {
    int id;
    int os;
    Server ** pointer;
public:
    explicit Server(int id =0, int os = 0, Server ** pointer = nullptr):
                       id(id), os(os), pointer(pointer) {}
    ~Server()= default;
    Server(const Server& s) = default;
    Server& operator=(const Server& s);
    int & ID();
    int & OS();
    Server ** ptrToFreeList();
    StatusType updateOS ();
    StatusType updateID(int id);
    void updatePointer (Server ** ptr);
};

class DataCenter{
    int id;
    int num_of_servers;
    Array <Server> servers;
    int num_of_linux;
    int num_of_windows;
    List <Server*> free_linux;
    List <Server*> free_windows;
public:
    DataCenter(int id, int num_of_servers);
    ~DataCenter() = default;
    DataCenter(DataCenter & DC) = default;
    int & ID();
    int & serversAmount();
    int & linuxAmount();
    int & windowsAmont();
    List <Server*> & FreeLinuxList();
    List <Server*> & FreeWindowsList();
    StatusType UpdateServerOs(int serverID);
    StatusType freeServer(int serverID);
    StatusType assignServer (int serverID);
};
#endif //WET_1_DATACENTER_SERVER_H
