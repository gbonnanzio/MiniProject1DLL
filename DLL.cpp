/*
 * DLL.cpp
 *
 *  Created on: Apr 2, 2020
 *      Geoffrey B. and Nick S.
 */
//Part 1:(20 pts) (addFirst (3pts) ,addAtFront(4 pts),push (4 pts),pop(4 pts)) + getting secret message:5 pts
//In the DLL.cpp class, get push, pop, and addFirst and addAtFront working for a doubly linked list as specified in DLL.hpp and DLL.cpp.
//For this section I've given you the test cases.  You should get the output I've given you for part 1. When you get those methods working, running this will decode the secret code 1
//
//Once you have that working, start on part 2 (note you will have to go into Coder.cpp and toggle
//comments for lines 64-110 to run part 2)
//
//Part 2: (15 pts)(insertAt(5 pts), removeAtK(5 pts)) +secret message: 5 pts
//Get  the DLL.cpp methods insertAt and removeAtK methods working for a doubly linked list.
//I've given you the test cases and the output.  When you get them working, you should be able to run this and decode the second secret code
//
//Once you have that working, start on part 3 (note that you will have to go to Coder.cpp and toggle comments for lines 112-137 to run part 3)
//
//Part 3: (8 pts) (reverse (4 pts)) + secret message: 4 pts
//For this part, you will get the method reverse working for the DLL doubly linked list class.
//This method reverses the list.  Note: it doesn't just print out the list in reverse order, it actually reverses the list, so if the original list was 3<->2<->4<->8, with 3 being first and 8 being last, the reversed list would be 8<->4<->2<->3 with 8 being first and 3 being last.
//
//once you have that working, start on part 4 (note that you will have to go to Coder.cpp and toggle
//comments for lines 139-215 to run part 4)
//
//Part 4: (11 pts) (removeX (5 pts), call by pointer) + secret message: 6 pts
//For this part, you will get the method removeX to work.  removeX removes the value x from the linked list, and uses call by pointer to change the index parameter to be the index (count) of where x occurred in the list.  So, for instance if you had:
//7<->8<->3<->5<->2<->6<->1
//And you called: removeX(3,&ind)
//When  you leave the method, you'd have
//7<->8<->5<->2<->6<->1
//And ind would hold 2
//
//Once you have this working, start on part 5.  For this you will have to go to Coder.cpp and toggle comments for lines  217- 251
//
//Part 5: (21 pts)(skip – recursive (13 pts) + secret message: 8 pts
//For this part, you will get the method skip working for the DLL doubly linked list class. This method RECURSIVELY deletes every other node.  If the boolean flag is set to true, it will delete every even node (i.e.,if the list was
//3<->2<->4<->5<->1<->7,
//the list that would result after the skip method was called would be:
//3<->4<->1.
//If the flag is set to false, the resulting list will be
//2<->5<->7
//NOTE:  For efficiency's sake, this method SHOULD NOT call removeAtK



#include "DNode.hpp"
#include "DLL.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

DLL::DLL(){  // constructor - initializes an empty list
	last = NULL;
	first = NULL;
	size = 0;
}
DLL::DLL(int x){  // constructor, initializes a list with one new node with data x
	DNode *n = new DNode (x);
	first = n;
	last = n;
	size=1;
}
/***************************************************************************************************/
/*Part 1																																		*/
/***************************************************************************************************/
/* write push, pop, addAtFront */


void DLL::push(int x){
	if(first == NULL){
		DNode *tmp = new DNode(x);
		first = tmp;
		last = first;
		size++;
	}
	else{
		DNode *tmp = new DNode(x);
		last -> next = tmp;
		tmp->prev = last;
		last = tmp;
		size++;
	}
}

int DLL::pop(){
	if(size == 1){
		int x = first->data;
		first = NULL;
		last = NULL;
		size--;
		return x;
	}


	DNode *temp = last;
	int x = temp->data;
	last = last->prev;
	delete temp;
	last->next = NULL;
	size--;
	return x;

}

void DLL::addFirst(int x){
	DNode *tmp = new DNode(x);
	first = tmp;
	last = first;
	size++;
}

void DLL::addAtFront(int x){
	DNode *tmp = new DNode(x);
	first->prev = tmp;
	tmp->next = first;
	first = tmp;
}

/***************************************************************************************************/
/*Part 2																																		*/
/***************************************************************************************************/
/* write insertAt, removeAtK  here */

void DLL::insertAt(int ind,int x){
	int currIndx = 0;
	//tmp will be the node before where we are inserting
	DNode *tmp = first;
	if(ind == 0){
		addAtFront(x);
	}
	else{
		while(currIndx < ind-1){
			tmp = tmp->next;
			currIndx++;
		}
		//tmp2 is the node after the insert
		DNode *tmp2 = tmp->next;
		if(tmp2 == NULL){
			push(x);
		}
		//node to insert
		else{
			DNode *newNode = new DNode(x); //new node
			tmp->next = newNode;
			newNode->next = tmp2;
			newNode->prev = tmp;
			tmp2->prev = newNode;
			size++;
		}
	}
}

int DLL::removeAtK(int ind){
	int currIndx = 0;
	int deletedData;
	//tmp will be the node before where we are inserting
	DNode *tmp = first;
	if(ind == 0){
		if(size == 1){
			deletedData = tmp->data;
			first = NULL;
			last = NULL;
			delete tmp;
			size--;
			return deletedData;
		}
		DNode *tmp2 = first->next;
		deletedData = first->data;
		delete first;
		first = tmp2;
		first->prev = NULL;
		size--;

	}
	else if(ind == size - 1){
		deletedData = pop();
	}
	else{
		while(currIndx < ind-1){
		tmp = tmp->next;
		currIndx++;
		}
		//tmp2 is the node to be removed
		DNode *tmp2 = tmp->next;
		deletedData = tmp2->data;
		//tmp3 is the node after the one removed
		DNode *tmp3 = tmp2->next;
		tmp->next = tmp3;
		tmp3->prev = tmp;
		delete tmp2;
		size--;
	}
	return deletedData;
}


/****************************************************************************************/
/* Part 3                                                                                                                       */
/****************************************************************************************/
/* write reverse here */

void DLL::reverse(){
	//tmp will be the current node
	DNode *tmp = first;
	//tmp2 will always be the original one after tmp
	// and will be what you're editing
	first = last;
	last = tmp;
	int count = 1;
	DNode *tmp2 = tmp->next;
	//for the last
	tmp->prev = tmp2;
	tmp->next = NULL;
	tmp = tmp2;
	tmp2 = tmp2->next;
	while(count < size-1){
		tmp->next = tmp->prev;
		tmp->prev = tmp2;
		tmp = tmp2;
		tmp2 = tmp2->next;
		count++;
	}
	tmp->next = tmp->prev;
	tmp->prev = NULL;
}







/****************************************************************************************/
/* Part 4                                                                                                                       */
/****************************************************************************************/
/* write removeX here */
	
void DLL:: removeX(int x, int *ind){
	DNode *tmp = first;
	int count = 0;
	*ind = -1;
	for(int i = 0; i<=size;i++){
		if(tmp == NULL){
			cout << count << endl;
			return;
		}
		if(tmp->data == x){
			if(count == 0){
				DNode *tmp2 = first->next;
				delete first;
				first = tmp2;
				first->prev = NULL;
				size--;
				*ind = count;
				return;
			}
			else if(count == size - 1){
				pop();
				cout << count << endl;
				*ind = count;
				return;
			}
			else{
				DNode *tmp2  = tmp->prev;
				DNode *tmp3 = tmp->next;
				tmp2->next = tmp3;
				tmp3->prev = tmp2;
				delete tmp;
				cout << count << endl;
				*ind = count;
				size--;
				return;
			}

		}
		tmp = tmp->next;
		count++;
	}
}


/****************************************************************************************/
/* Part 5                                                                                                                     */
/****************************************************************************************/
/* write skip here */

void DLL::skip(bool flag, int ct, DNode *tmp) {
	if (flag == true) {
		if (tmp == last) {
			if (ct % 2 == 0) {
				pop();
				return;
			} else {
				return;
			}
		} else if (ct % 2 == 0) {
			if (ct == 0) {
				DNode *tmp2 = first->next;
				first = tmp2;
				first->prev = NULL;
				size--;
				ct++;
				skip(true, ct, tmp2);
			}

			else {
				DNode *tmp2 = tmp->prev;
				DNode *tmp3 = tmp->next;
				tmp2->next = tmp3;
				tmp3->prev = tmp2;
				size--;
				ct++;
				skip(true, ct, tmp3);
			}
		}

		else {
			ct++;
			skip(true, ct, tmp->next);
		}
	}

	else {
		if (tmp == last) {
					if (ct % 2 == 1) {
						pop();
						return;
					} else {
						return;
					}
				} else if (ct % 2 == 1) {

						DNode *tmp2 = tmp->prev;
						DNode *tmp3 = tmp->next;
						tmp2->next = tmp3;
						tmp3->prev = tmp2;
						size--;
						ct++;
						skip(false, ct, tmp3);

				}

				else {
					ct++;
					skip(false, ct, tmp->next);
				}
			}
}

/***************************************************************************************************/
/*End of your part																														*/
/***************************************************************************************************/

void DLL::printList() {
	DNode *tmp = first;
	while (tmp != NULL) {
		cout << tmp->data << ", ";
		tmp = tmp->next;
	}
	cout << endl;
}
void DLL::printCode() {
	DNode *tmp = first;
	while (tmp != NULL) {
		cout << alpha[tmp->data];
		tmp = tmp->next;
	}
	cout << endl;
}
DLL::~DLL(){
	DNode *tmp = first;
	DNode *tmp2 = first->next;
	while (tmp != NULL) {
		delete tmp;
		tmp = tmp2;
		tmp2 = tmp2->next;
	}
}



