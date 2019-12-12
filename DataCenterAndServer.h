
#ifndef WET_1_DATACENTER_SERVER_H
#define WET_1_DATACENTER_SERVER_H

#include "Array.h"
#include "list.h"

typedef enum {
	SUCCESS_DC = 0,
	FAILURE_DC = -1,
	ALLOCATION_ERROR_DC = -2,
	INVALID_INPUT_DC = -3
} StatusTypeDC;

class Server {
	int os;
	ListItem <Server>* pointer;
public:
	int id;
	explicit Server(int id = 0, int os = 0, ListItem <Server>* pointer = nullptr) :
		id(id), os(os), pointer(pointer) {}
	~Server() = default;
	Server(const Server& s) = default;
	Server& operator=(const Server& s);
	int & ID();
	int & OS();
	ListItem <Server>* ptrToFreeList();
	StatusTypeDC updateOS();
	StatusTypeDC updateID(int Id);
	void updatePointer(ListItem <Server>* ptr);
};

class DataCenter {
	int id;
	int num_of_servers;
	Array <Server> servers;
	int num_of_linux;
	int num_of_windows;
	List <Server> free_linux;
	List <Server> free_windows;
public:
	DataCenter(int id, int num_of_servers);
	~DataCenter() = default;
	DataCenter(DataCenter & DC) = default;
	int & ID();
	int & serversAmount();
	int & linuxAmount();
	int & windowsAmont();
	List <Server> & FreeLinuxList();
	List <Server> & FreeWindowsList();
	StatusTypeDC UpdateServerOs(int serverID);
	StatusTypeDC freeServer(int serverID);
	StatusTypeDC assignServer(int serverID);
	Server * getServer(int serverID);
};
#endif //WET_1_DATACENTER_SERVER_H