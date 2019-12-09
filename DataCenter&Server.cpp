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

StatusType Server::updateOS() {
    if (os ==1)
        this->os = 0;
    else this->os = 1;
    return SUCCESS;
}

StatusType Server::updateID(int id) {
    if (id < 0)
        return INVALID_INPUT;
    this->id = id;
    return SUCCESS;
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

StatusType DataCenter::UpdateServerOs(int serverID) {
    if (serverID <0 || serverID>= num_of_servers)
        return  INVALID_INPUT;
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
    return SUCCESS;
}

StatusType DataCenter::freeServer(int serverID) {
    if (serverID <0 || serverID>= num_of_servers)
        return  INVALID_INPUT;
    Server *list_component = &servers[serverID];
    if(servers[serverID].updateOS() ==1){
        free_windows.PushBack(list_component);
        servers[serverID].updatePointer(free_windows.GetTail());
    }
    else{
        free_linux.PushBack(list_component);
        servers[serverID].updatePointer(free_linux.GetTail());
    }
    return SUCCESS;
}

StatusType DataCenter::assignServer(int serverID) {
    if (serverID <0 || serverID>= num_of_servers)
        return  INVALID_INPUT;
    ListItem <Server*>* list_component = servers[serverID].ptrToFreeList();
    servers[serverID].updatePointer(nullptr);
    if(servers[serverID].updateOS() ==1)
        free_windows.DeleteItem(list_component);
    else free_linux.DeleteItem(list_component);
    return SUCCESS;
}

