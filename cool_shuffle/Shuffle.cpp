/*********************************************************************************
* Sean Rowley, sarowley
* 2023 Winter CSE101 PA5
* Shuffle.c
*********************************************************************************/
#include<iostream>
#include<fstream>
#include<string>
#include "List.h"

using namespace std;


void shuffle(List& D){
	if (D.length() == 1){
		return;
	}
	List firsthalf, secondhalf;
	int firstlength; 
	int secondlength;

	if (D.length() % 2 != 0){
		firstlength = D.length()/2;
		secondlength = D.length()/2+1;
	}
	else{
		firstlength = D.length()/2;
		secondlength = D.length()/2;
	}

	D.moveFront();
	for (int i = 0; i<firstlength; i++){
		firsthalf.insertBefore(D.peekNext());
		D.moveNext();
	}
	for (int i = 0; i<secondlength; i++){
		secondhalf.insertBefore(D.peekNext());
		D.moveNext();
	}

	D.clear();
	firsthalf.moveFront();
	secondhalf.moveFront();

	int combo_length = firstlength + secondlength;

	for (int i = 0; i < combo_length; i++){
		if (i % 2 == 1 && firsthalf.length() > 0){
			D.insertBefore(firsthalf.peekNext());
			firsthalf.moveNext();
		}
		else{
			D.insertBefore(secondhalf.peekNext());
			secondhalf.moveNext();	
		}
	}

	return;
}


int main(int argc, char * argv[]){
	int size = atol(argv[1]);
	
	if (size < 1){
		throw std::invalid_argument("trying to shuffle with a non-existant deck");
		exit(EXIT_FAILURE);
	}
	cout << "deck size       shuffle count\n";
	cout << "------------------------------\n";

	List D;
	List before_shuffling;
	for (int i = 0; i < size; i++){
		D.insertBefore(i);
		before_shuffling.insertBefore(i);
		int shuffle_num = 0;
		
		shuffle(D);
		shuffle_num += 1;

		while(!(D == before_shuffling)){
			shuffle(D);
			shuffle_num += 1;
		}
		if (i+1 < 10){
			cout << left << i+1 << "                "  << shuffle_num << endl;
		}
		else if (i+1 < 100){
			cout << left << i+1 << "               " << shuffle_num << endl;
		}
		else if (i+1 < 1000){
			cout << left << i+1 << "              " << shuffle_num << endl;
		}
		else if (i+1 < 10000){
                        cout << left << i+1 << "             "  << shuffle_num << endl;
                }
                else if (i+1 < 100000){
                        cout << left << i+1 << "            " << shuffle_num << endl;
                }
                else if (i+1 < 1000000){
                        cout << left << i+1 << "           " << shuffle_num << endl;
                }
		else { //i know there's probably a smart way to go about this, but here's to hoping
			cout << left << i+1 << "          " << shuffle_num << endl;
		}
	}
	return 0;
}

