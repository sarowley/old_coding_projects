/*********************************************************************************
* Sean Rowley, sarowley
* 2023 Winter CSE101 PA5
* ListTest.cpp
*********************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){

   int i, n=20;
   List A, B;

   for(i=1; i<=n; i++){
      A.insertAfter(i);
      B.insertBefore(i);
   }

   cout << endl;
   cout << "List A: " << A << endl;
   cout << "Position of A: " << A.position() << endl;
   cout << "List B: " << B << endl;
   cout << "Position of B: " << B.position() << endl;
   cout << endl;

   A.moveFront();
   cout << "moving a to front" << endl;
   B.moveBack();
   cout << "moving b to back" << endl;

   //make new list and set them equal and check if equal
   List C = A;
   cout << "C == A is " << (C==A?"true":"false") << endl;
   //length()
   cout << "length: " << A.length() << endl;
   //front()
   cout << "front: " << A.front() << endl;
   //back()
   cout << "back: " << A.back() << endl;
   //peekNext()
   cout << "peeknext: " << A.peekNext() << endl;
   //peekPrev()
   cout << "peekprev: " << A.peekPrev() << endl;
   //clear
   cout << "List C: " << C << endl;
   C.clear();
   cout << "List C: " << C << endl;
   //setBefore()
   A.setBefore(12);
   cout << "List A: " << A << endl;
   //eraseAfter()
   A.eraseAfter();
   cout << "List A: " << A << endl;
   //eraseBefore()
   A.eraseBefore();
   cout << "List A: " << A << endl;
   //findNext()
   B.moveFront();
   cout << B.findNext(10) << endl;
   //findPrev()
   B.moveBack();
   cout << B.findPrev(10) << endl;
   //cleanup()
   cout << "List A: " << A << endl;
   A.insertBefore(12);
   cout << "List A: " << A << endl;
   A.cleanup();
   cout << "List A: " << A << endl;

   return( EXIT_SUCCESS );
}
