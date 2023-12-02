/*********************************************************************************
* Sean Rowley, sarowley
* 2023 Winter CSE101 PA5
* List.cpp
*********************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include "List.h"


   // Class Constructors & Destructors ----------------------------------------

   //this one is private  
   List::Node::Node(ListElement x){
	data = x;
	next = nullptr;
	prev= nullptr;
   }
 
   // Creates new List in the empty state.
   List::List(){
	frontDummy = new Node(-13);
	backDummy = new Node(-13);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	afterCursor = backDummy;
	beforeCursor = frontDummy;
	pos_cursor = 0;
	num_elements = 0;
   }

   // Copy constructor.
   List::List(const List& L){
	frontDummy = new Node(-13);
	backDummy = new Node(-13);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;
	Node* N = L.frontDummy->next;
	while (N->next != nullptr){
		this->insertBefore(N->data);
		N = N->next;
	}   
   }

   // Destructor
   List::~List(){
	this->moveFront();
	while (num_elements > 0){
		this->eraseAfter();
	}
	delete frontDummy;
	delete backDummy;   
   }

   // Access functions --------------------------------------------------------

   // length()
   // Returns the length of this List.
   int List::length() const{
	return(num_elements);
   }

   // front()
   // Returns the front element in this List.
   // pre: length()>0
   ListElement List::front() const{
	if (num_elements==0){
		throw std::length_error("List: front(): empty list");
	}
	return(frontDummy->next->data); 
   }

   // back()
   // Returns the back element in this List.
   // pre: length()>0
   ListElement List::back() const{
	if (num_elements == 0){
		throw std::length_error("List: back(): empty list");
	}
	return (backDummy->prev->data); 
   }

   // position()
   // Returns the position of cursor in this List: 0 <= position() <= length().
   int List::position() const{
	if (pos_cursor < 0 || pos_cursor > num_elements){
		throw std::range_error("List: position(): cursor out of range");
	}
	return (pos_cursor);
   }

   // peekNext()
   // Returns the element after the cursor.
   // pre: position()<length()
   ListElement List::peekNext() const{
	if (pos_cursor > num_elements){
		throw std::range_error("List: peekNext(): cursor at back");
	}
	return (afterCursor->data);
   }

   // peekPrev()
   // Returns the element before the cursor.
   // pre: position()>0
   ListElement List::peekPrev() const{
	if (pos_cursor < 1){
		throw std::range_error("List: peekPrev(): cursor at front");
	} 
	return (beforeCursor->data);
   }


   // Manipulation procedures -------------------------------------------------

   // clear()
   // Deletes all elements in this List, setting it to the empty state.
   void List::clear(){
	this->moveFront();
	while (num_elements > 0){
		this->eraseAfter();
	}
   }

   // moveFront()
   // Moves cursor to position 0 in this List.
   void List::moveFront(){
	pos_cursor = 0;
	beforeCursor = frontDummy;
	afterCursor = frontDummy->next;
   }

   // moveBack()
   // Moves cursor to position length() in this List.
   void List::moveBack(){
	pos_cursor = num_elements;
	afterCursor = backDummy;
	beforeCursor = backDummy->prev;
   }

   // moveNext()
   // Advances cursor to next higher position. Returns the List element that
   // was passed over. 
   // pre: position()<length() 
   ListElement List::moveNext(){
	if (pos_cursor > num_elements){
		throw std::range_error("List: moveNext(): cursor at back");
	}
	beforeCursor = beforeCursor->next;
	afterCursor = afterCursor->next;
	pos_cursor += 1;
   	return (beforeCursor->data);
   }

   // movePrev()
   // Advances cursor to next lower position. Returns the List element that
   // was passed over. 
   // pre: position()>0
   ListElement List::movePrev(){
	if (pos_cursor == 0){
		throw std::range_error("List: movePrev(): cursor at front");
	}
	beforeCursor = beforeCursor->prev;
	afterCursor = afterCursor->prev;
	pos_cursor += -1;
	return (afterCursor->data);
   }

   // insertAfter()
   // Inserts x after cursor.
   void List::insertAfter(ListElement x){
	Node* N = new Node(x);
	N->prev = beforeCursor;
	N->next = afterCursor;
	beforeCursor->next = N;
	afterCursor->prev = N;
	afterCursor = N;
	num_elements += 1;

   }

   // insertBefore()
   // Inserts x before cursor.
   void List::insertBefore(ListElement x){
	Node* N = new Node(x);
	N->prev = beforeCursor;
	N->next = afterCursor;
	beforeCursor->next = N;
	afterCursor->prev = N;
	beforeCursor = N;
	pos_cursor += 1;
	num_elements += 1;
   }

   // setAfter()
   // Overwrites the List element after the cursor with x.
   // pre: position()<length()
   void List::setAfter(ListElement x){
	if (pos_cursor > num_elements){
		throw std::range_error("List: setAfter(): cursor at back");
	}
	afterCursor->data = x;
   }

   // setBefore()
   // Overwrites the List element before the cursor with x.
   // pre: position()>0
   void List::setBefore(ListElement x){
	if (pos_cursor < 1){
		throw std::range_error("List: setBefore(): cursor at front");
	}
	beforeCursor->data = x;
   }

   // eraseAfter()
   // Deletes element after cursor.
   // pre: position()<length()
   void List::eraseAfter(){
	if (pos_cursor > num_elements){
		throw std::range_error("List: eraseAfter(): cursor at back");
	}
	Node* N = afterCursor;
	afterCursor = N->next;
	beforeCursor->next = afterCursor;
	afterCursor->prev = beforeCursor;
	delete N;
	num_elements += -1;
   }

   // eraseBefore()
   // Deletes element before cursor.
   // pre: position()>0
   void List::eraseBefore(){
	if (pos_cursor < 1){
		throw std::range_error("List: eraseBefore(): cursor at front");
	}
	Node* N = beforeCursor;
	beforeCursor = N->prev;
	afterCursor->prev = beforeCursor;
	beforeCursor->next = afterCursor;
	delete N;
	pos_cursor += -1;
	num_elements += -1;
   }


   // Other Functions ---------------------------------------------------------

   // findNext()
   // Starting from the current cursor position, performs a linear search (in 
   // the direction front-to-back) for the first occurrence of element x. If x
   // is found, places the cursor immediately after the found element, then 
   // returns the final cursor position. If x is not found, places the cursor 
   // at position length(), and returns -1. 
   int List::findNext(ListElement x){
	if (pos_cursor > num_elements){
		throw std::range_error("List: findNext(): cursor at back");
	}
	if (num_elements < 1){
		throw std::length_error("List: findNext(): empty list");
	}
	for (int i = pos_cursor; i < num_elements; i++){
		this->moveNext();
		if (beforeCursor->data == x){
			return pos_cursor;
		}
	}


	moveBack();
	return -1;
   }

   // findPrev()
   // Starting from the current cursor position, performs a linear search (in 
   // the direction back-to-front) for the first occurrence of element x. If x
   // is found, places the cursor immediately before the found element, then
   // returns the final cursor position. If x is not found, places the cursor 
   // at position 0, and returns -1. 
   int List::findPrev(ListElement x){
	if (pos_cursor < 1){
		throw std::range_error("List: findPrev(): cursor at front");
	}
	if (num_elements < 1){
		throw std::length_error("List: findPrev(); empty list");
	}
	for (int i = pos_cursor; i > 0; i--){
		this->movePrev();
		if (afterCursor->data == x){
			return pos_cursor;
		}
	}
	moveFront();
	return -1;
   }

   // cleanup()
   // Removes any repeated elements in this List, leaving only unique elements.
   // The order of the remaining elements is obtained by retaining the frontmost 
   // occurrance of each element, and removing all other occurances. The cursor 
   // is not moved with respect to the retained elements, i.e. it lies between 
   // the same two retained elements that it did before cleanup() was called.
   void List::cleanup(){
	Node* N = this->frontDummy->next;
	int count = 0;
	while (N->next != nullptr){
		Node* help = N->next;
		Node* temp = nullptr;
		int countUp = count + 1;

		while (help->next != nullptr){
			temp = help->next;
			if (help->data == N->data){
				help->prev->next = help->next;
				help->next->prev = help->prev;

				if (help == afterCursor){
					afterCursor = afterCursor->next;
				}
				if (help == beforeCursor){
					beforeCursor = beforeCursor->prev;
				}
				if (countUp < pos_cursor){
					pos_cursor += -1;
				}

				delete help;
				num_elements += -1;
				countUp += -1;

			}

			help = temp;
			countUp += 1;
		}

		N = N->next;
		count += 1;
	}
   }
 
   // concat()
   // Returns a new List consisting of the elements of this List, followed by
   // the elements of L. The cursor in the returned List will be at postion 0.
   List List::concat(const List& L) const{
	List J;
	Node* N = this->frontDummy->next;
	Node* M = L.frontDummy->next;
	while (N->next!=nullptr){
		J.insertBefore(N->data);
		N = N->next;
	}
	while (M->next!=nullptr){
		J.insertBefore(M->data);
		M = M->next;
	}
	J.moveFront();
   	return J;
   }

   // to_string()
   // Returns a string representation of this List consisting of a comma 
   // separated sequence of elements, surrounded by parentheses.
   std::string List::to_string() const{
	std::string s = "";

	if (num_elements!=0){
		Node* N = frontDummy->next;
		while (N->next->next != nullptr){
			s += std::to_string(N->data)+", ";
			N = N->next;
		}

		s += std::to_string(N->data);
	}
	
	return "(" + s + ")";
   }

   // equals()
   // Returns true if and only if this List is the same integer sequence as R.
   // The cursors in this List and in R are unchanged.
   bool List::equals(const List& R) const{
	bool eq = false;
	Node* N = nullptr;
	Node* M = nullptr;

	eq = (this->num_elements == R.num_elements);
	N = this->frontDummy->next;
	M = R.frontDummy->next;
	while (eq && N->next!=nullptr){
		eq = (N->data==M->data);
		N = N->next;
		M = M->next;
	}
	return eq;
   }


   // Overriden Operators -----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of L into stream.
   std::ostream& operator<<( std::ostream& stream, const List& L ){
	return stream << L.List::to_string();
    }

   // operator==()
   // Returns true if and only if A is the same integer sequence as B. The 
   // cursors in both Lists are unchanged.
   bool operator==( const List& A, const List& B ){
	return A.List::equals(B);
   }

   // operator=()
   // Overwrites the state of this List with state of L.
   List& List::operator=( const List& L ){
	if (this != &L){
		List temp = L;

		std::swap(frontDummy, temp.frontDummy);
		std::swap(backDummy, temp.backDummy);
		std::swap(num_elements, temp.num_elements);
	}
	return *this;

   }
