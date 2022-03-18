//Lydia K Fritz
//2/14/2019
//Provided C++ DLinkedList
#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include <iostream>

using namespace std;

template <class T>
class DLinkedList {

	//PROVIDED
	friend ostream & operator<<(ostream & out, const DLinkedList<T> & rhs) {
		DNode * curr = rhs.header;
		while (curr != NULL) {
			out << curr->data << " ";
			curr = curr->next;
		}
		return out;
	}

public:

	//inner class DNode PROVIDED
	class DNode {
	public:
		DNode * next;
		DNode * prev;
		T data;

		DNode(T val = T()) {
			data = val;
			next = prev = this;
		}
		
	};

	//create an empty list:  PROVIDED
	DLinkedList() {
		//create the header
		header = NULL;		
	}

	//add method  PROVIDED
	DNode * add(T item) {
		//add a new node and return a 
		//pointer to this node
		DNode * newNode = new DNode(item);
		newNode->prev = header;
		newNode->next = header->next;
		header->next->prev = newNode;
		header->next = newNode;
		return newNode;
	}

	/**
	* ASSIGNED
	* remove val from the list
	*
	* @param val
	* @return true if successful, false otherwise
	*/
	bool remove(T val) {
		DNode* temp = header;
		while (temp != NULL) {
			if (temp -> data == val) {
				if (temp -> prev == NULL) {
					header = temp -> next;
					header -> prev = NULL;
				}
				else if(temp -> next == NULL) {
					temp -> prev -> next = NULL;
				}
				else {
					cout << "Removing" << temp->data << endl;
					temp -> next -> prev = temp -> prev;
					temp -> prev -> next = temp -> next;
				}
				delete(temp);
				return true; 
			}
			temp = temp -> next; 
		}
		return false;
	}
	

	/**
	* ASSIGNED
	*
	* @param item
	*/
	void insertOrder(T item) {
		DNode *newNode = new DNode;
		
		newNode->next = NULL;
		newNode->data = item;

		if (header == NULL) {
			header = newNode;
			return;
		}
		else {
			DNode *node = header->next;
			DNode *last = header;
			if (header->data > item) {
				newNode->next = header;
				header->prev = newNode;
				header = newNode;
				return;
			}
			else {
				while (node != NULL) {
					if (newNode->data < node->data) {
						newNode->next = node;
						newNode->prev = node->prev;
						node->prev->next = newNode;
						node->prev = newNode;
						if (header != NULL) {
							header->prev = NULL;
							return;
						}
					}
					last = node;
					node = node->next;
				}
			}
			last->next = newNode;
			newNode->prev = last;
			header->prev = NULL;
		}
	}

	/**
	* ASSIGNED
	*
	* @param item
	*/
	bool insertOrderUnique(T item) {
		DNode *uniqueI = header;
		bool isUnique = true;

		while (uniqueI != NULL) {
			if (uniqueI->data == item) {
				isUnique = false;
				break;
			}
			uniqueI = uniqueI->next;
		}
		if (isUnique) {
			insertOrder(item);
			return true;
		}
		else {return false;}
	}

	/**
	* ASSIGNED
	* PRE:  this and rhs are sorted lists
	* @param rhs
	* @return list that contains this and rhs merged into a sorted list
	* POST:  returned list will not contain duplicates, both rhs and this
	* will have no elements
	*/
	DLinkedList merge(DLinkedList rhs) {
		DLinkedList result;
		DNode *temp = header;
		while (temp != NULL) {
			result.insertOrder(temp->data);
			temp = temp->next;
		}
		delete temp;
		DNode *tempRhs = rhs.header;
		while (tempRhs != NULL) {
			result.insertOrderUnique(tempRhs->data);
			tempRhs = tempRhs->next;;
		}
		delete tempRhs;
		return result;
	}

	
private:
	//DLinkedList fields:  PROVIDED
	DNode * header;	

};


#endif