#ifndef SINGLE_LIST_H
#define SINGLE_LIST_H
 
#include "ece250.h"
#include "Single_node.h"
#include "Exception.h"


template <typename Object>
class Single_list {
	private:
		Single_node<Object> *list_head;
		Single_node<Object> *list_tail;
		int node_count;

	public:
		Single_list();
		Single_list( const Single_list & );
		~Single_list();

		Single_list &operator = ( const Single_list & );

		// Accessors

		int size() const;
		bool empty() const;

		Object front() const;
		Object back() const;

		Single_node<Object> *head() const;
		Single_node<Object> *tail() const;

		int count( const Object & ) const;

		// Mutators

		void push_front( const Object & );
		void push_back( const Object & );

		Object pop_front();

		int erase( const Object & );
		void remove_max(); 
	// Friends

	template <typename T>
	friend std::ostream &operator << ( std::ostream &, const Single_list<T> & );
};

template <typename Object>
Single_list<Object>::Single_list():list_head(0), list_tail(0), node_count(0) {
	// empty constructor
}

template <typename Object>
Single_list<Object>::Single_list( const Single_list<Object> &list ):list_head(0), list_tail(0), node_count(0) {
	*this = list;
}

template <typename Object>
Single_list<Object>::~Single_list() {
 	while (!empty()){
		pop_front();
	}
	 
}

template <typename Object>
Single_list<Object> &Single_list<Object>::operator = ( const Single_list<Object> &rhs ) {
	// empty the current object
	// make a copy of the list rhs
	
	if (rhs.empty()) {
		return *this;
	}
	
	while (!empty()) {
		pop_front();
	}
	
	
	
	//a pointer points to the first node of the list
 	Single_node<Object> *tmp = rhs.list_head;
	
	//list is built using the  push_back function implemented below.
	while (tmp != 0)
	{
		push_back(tmp -> retrieve());
		tmp = tmp -> next_node;
	}
	
	return *this;
	
	
}

template <typename Object>
int Single_list<Object>::size() const {
 	return node_count;
}

template <typename Object>
bool Single_list<Object>::empty() const {
  if (size() == 0) {
	//if (size() == 0) {
 	  return true;
  }
	return false;
}

template <typename Object>
Object Single_list<Object>::front() const {
	if (empty()) {
		throw underflow();
	}
	
	return head() -> retrieve();
}

template <typename Object>
Object Single_list<Object>::back() const {
	if(empty())
	{
		throw underflow();
	}
	return tail() -> retrieve();
}

template <typename Object>
Single_node<Object> *Single_list<Object>::head() const {
 	return list_head;
}

template <typename Object>
Single_node<Object> *Single_list<Object>::tail() const {
	return list_tail;
}

template <typename Object>
int Single_list<Object>::count( const Object &obj ) const {
	
	Single_node<Object> *tmp_count;
	tmp_count = head();
	Object retrieved_val;

	while (tmp_count != 0) {
		retrieved_val = tmp_count -> retrieve();
		if (retrieved_val == obj) {
			return 1;
		}
		else {
			tmp_count = tmp_count -> next();
		}

	}
	
		return 0;
 
}

template <typename Object>
void Single_list<Object>::push_front( const Object &obj ) {

	Single_node<Object> *tmp_first; 

	//if list initially empty
	if (empty()) {
		//create node with tmp pointer
 		tmp_first = new Single_node<Object>(obj, 0);
		//update the head pointer
		list_head = tmp_first;
		list_tail = tmp_first;
	}
	else {
		//create node with tmp pointer
 		tmp_first = new Single_node<Object>(obj, list_head);
		//update the head pointer
		list_head = tmp_first;
 	}
	
	++node_count; 
 
}

template <typename Object>
void Single_list<Object>::push_back( const Object &obj ) {

	Single_node<Object> *tmp_back;
	tmp_back = new Single_node<Object>(obj, 0);

	if (empty()) {
		list_tail = tmp_back; 
		list_head = tmp_back;
 	}
	else{
 
 		list_tail -> next_node = tmp_back;
		list_tail = tmp_back; 
 	}
	++node_count; 
}

template <typename Object>
Object Single_list<Object>::pop_front() {
	
	if (empty()) {
		throw underflow();
	}
	
	Single_node<Object> *tmp_front;  
	Object hold;
	 
	hold = front();
	tmp_front = head();
	
	if(size() == 1){
		list_head = 0;
		list_tail = 0; 
	 
	}
	else {
	    list_head = head() -> next();
	}
 
	delete tmp_front;
	
 	--node_count;
	return hold;
	
}

template <typename Object>
int Single_list<Object>::erase( const Object &obj ) {
	
	if (empty()) {
		throw underflow();
	}
	
	Single_node<Object> *to_be_deleted; 
	
	//found in first node
	if (front() == obj) {
		
		to_be_deleted = head();
		list_head = head() -> next();
		delete to_be_deleted;
		--node_count;
		return 1;
	}
	//found in last node
	else if(back() == obj){
		
		to_be_deleted = tail();
		Single_node<Object> *travel;
		for (travel=head(); travel -> next() != tail(); travel -> next());
		list_tail = travel;
		travel = travel -> next();
		delete travel;
		--node_count;
		return 1;
		
	}
	//found in a node in between
	else {
		
		for (to_be_deleted = head(); to_be_deleted != 0; to_be_deleted -> next()){
		
			if(to_be_deleted -> retrieve() == obj){

				Single_node<Object> *follower;
	
				for (follower = head(); follower -> next() != to_be_deleted; follower->next());
				follower -> next_node = to_be_deleted -> next();
				delete to_be_deleted;
				--node_count;
				return 1;
			}
			
		}
		//not found
		return 0;
	}
	
}


template <typename Object>
void Single_list<Object>::remove_max()
{
	if (empty()) {
		throw underflow();
	}
	int hold_max = 0;
	Single_node<Object> *max;
	Single_node<Object> *ptr1;
	Single_node<Object> *ptr2;
	Single_node<Object> *tmp = head();

	ptr1 = head();
	ptr2 = head() -> next();
	while (ptr2 != 0) {
		if (ptr1 -> retrieve() > ptr2 -> retrieve()) {
			if (hold_max == ptr1 -> retrieve()) {
				max = ptr1;
			}
			else if(hold_max < ptr1 -> retrieve()){
				hold_max = ptr1-> retrieve();
				max = ptr1;
			}
		}
		else {
			// ptr2 content > ptr1 content
			if (hold_max == ptr2 -> retrieve()) {
				max = ptr2;
			}
			else if(hold_max < ptr2 -> retrieve()){
				hold_max = ptr2 -> retrieve();
				max = ptr2;
			}
		}
		
		ptr1 = ptr1 -> next();
		ptr2 = ptr2 -> next();
	}
	
	if (max == head()) {
		list_head = head() -> next();
		 
	}
	else if(max == tail())
	{
		while (tmp -> next() != tail()) {
			tmp = tmp -> next();
		}
		
		list_tail = tmp;
 	}
	
	else {
		while (tmp -> next() != max) {
			tmp = tmp -> next();
		}
		
		tmp -> next_node = max -> next();
		 
	}
	
	//output
	std:: cout<< "The node that will be deleted is: " << max -> retrieve();
	std:: cout<< "\n" << "If max was tail then tail is changed to: "<< tail() -> retrieve();
	std:: cout<< "\n";
	//std:: cout<< "Next node in list [from last node that contains the maximum value] is: "<< max -> next()-> retrieve();
	std:: cout<< "\n";
	 
	delete max;
	--node_count;
}



// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator << ( std::ostream &out, const Single_list<T> &list ) {
	for ( Single_node<T> *ptr = list.head(); ptr != 0; ptr = ptr->next() ) {
		out << " -> " << ptr->retrieve();
	}

	out << " -> 0";

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
