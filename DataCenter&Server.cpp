//
// Created by Uriel on 04-Dec-19.
//
#include "Array.h"
#include "list.h"
#include "DataCenter&Server.h"

#include <iostream>
/**********implementing server*********/

Server& Server::operator=(const Server &s) {
    this->pointer = s.pointer;
    this->pointer = s.pointer;
    this->id = s.id;
    return *this;
}

int &Server::ID() {
    return id;
}

int &Server::OS() {
    return os;
}

ListItem <Server*>* Server::ptrToFreeList() {
    return pointer;
}

StatusTypeDC Server::updateOS() {
    if (os ==1)
        this->os = 0;
    else this->os = 1;
    return SUCCESS_DC;
}

StatusTypeDC Server::updateID(int id) {
    if (id < 0)
        return INVALID_INPUT_DC;
    this->id = id;
    return SUCCESS_DC;
}

void Server::updatePointer( ListItem <Server*>* ptr) {
    this->pointer  = ptr;
}


/**********implementing DataCenter*********/
DataCenter::DataCenter(int id, int num_of_servers): id(id), num_of_servers(num_of_servers), num_of_linux(num_of_servers),
                    num_of_windows(0), servers(Array <Server>(num_of_servers)){
    Array <Server> s(num_of_servers);
    List <Server*> l1, l2;
    free_linux = l1;
    free_windows = l2;
    for (int i = 0; i < num_of_servers ; ++i) {
        servers[i].updateID(i);
        Server* list_component = &servers[i];
        this->free_linux.PushBack(list_component);
        servers[i].updatePointer(free_linux.GetTail());

    }
}

int &DataCenter::ID() {
    return id;
}

int &DataCenter::serversAmount() {
    return num_of_servers;
}

int &DataCenter::linuxAmount() {
    return num_of_linux;
}

int &DataCenter::windowsAmont() {
    return num_of_windows;
}

List<Server*> &DataCenter::FreeLinuxList() {
    return free_linux;
}

List<Server*> &DataCenter::FreeWindowsList() {
    return free_windows;
}

StatusTypeDC DataCenter::UpdateServerOs(int serverID) {
    if (serverID <0 || serverID>= num_of_servers)
        return  INVALID_INPUT_DC;
    int unupdatedOS = servers[serverID].OS();
    servers[serverID].updateOS();
    //ListItem <Server*>* list_item_to_move = servers[serverID].ptrToFreeList();
    if (unupdatedOS == 1){
        //free_windows.DeleteItem(list_item_to_move);
        //free_linux.PushBack(list_item_to_move);
        num_of_windows--;
        num_of_windows++;
    }
    else {
        //free_linux.DeleteItem(list_item_to_move);
        //free_windows.PushBack(list_item_to_move);
        num_of_windows++;
        num_of_windows--;
    }
    return SUCCESS_DC;
}

StatusTypeDC DataCenter::freeServer(int serverID) {
    if (serverID <0 || serverID>= num_of_servers)
        return  INVALID_INPUT_DC;
    Server *list_component = &servers[serverID];
    if(servers[serverID].updateOS() ==1){
        free_windows.PushBack(list_component);
        servers[serverID].updatePointer(free_windows.GetTail());
    }
    else{
        free_linux.PushBack(list_component);
        servers[serverID].updatePointer(free_linux.GetTail());
    }
    return SUCCESS_DC;
}

StatusTypeDC DataCenter::assignServer(int serverID) {
    if (serverID <0 || serverID>= num_of_servers)
        return  INVALID_INPUT_DC;
    ListItem <Server*>* list_component = servers[serverID].ptrToFreeList();
    if (list_component == nullptr)
        return  FAILURE_DC;
    servers[serverID].updatePointer(nullptr);
    if(servers[serverID].OS() ==1)
        free_windows.DeleteItem(list_component);
    else free_linux.DeleteItem(list_component);
    return SUCCESS_DC;
}

Server * DataCenter::getServer(int serverID) {
    if (serverID <0 || serverID>= num_of_servers)
        return nullptr;
    return &servers[serverID];
}

