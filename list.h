#ifndef LIST_H
#define LIST_H 


#include <iostream>

using namespace std;

template<class T>
class ListItem {

T data;
ListItem<T>* next;
ListItem<T>* prev;

public:
	ListItem(const T& value) : data(value), next(NULL), prev(NULL) {} 
	~ListItem() {}

	void SetValue(const T& value);
	const T& GetValue() const;
	void SetNext(ListItem<T>* next_item);
	ListItem<T>* GetNext() const;
	void SetPrev(ListItem<T>* prev_item);
	ListItem<T>* GetPrev() const;
	void Print() const;//for debugging purpuses//

private:
	ListItem();  // Prevent calling the default ctor
};

template <class T>
class List {

ListItem<T>* head;
ListItem<T>* tail;

public:
	List() : head(NULL), tail(NULL) {}
	~List();

	//insert value into a listitem type and then insert
	//the listitem into the begining of the list
	//returns pointer to the newly created listitem or null if there was an error
	ListItem<T>* PushFront(const T& value);
	ListItem<T>* PushBack(const T& value);

	/*not nedded for us
	bool PopFront(T* value);
	bool PopBack(T* value);
	*/

	int size() const;//for debugging purpuses//
	void Print() const;//for debugging purpuses//

	/* not nedded for us
	bool Insert(const T& value, const int& position);
	*/

	/*not nedded for us
	bool Delete(const int& position);
	*/

	bool DeleteItem(ListItem<T>* item_to_delete);//delet a listitem

	T PopItem(ListItem<T>* item_to_pop);//delet a listitem and return the data it was holding in it

	//insert data into a listitem and place it after item_before in the list
	ListItem<T>* Insert_after(ListItem<T>* item_before, const T& value);

	/*not nedded for us
	int  Find(const int& value) const;
	bool Get(const int& position, T* value);
	*/

	ListItem<T>* GetHead() const;//return the first listitem in the list
	ListItem<T>* GetTail() const;//return the last listitem in the list
};


#endif
