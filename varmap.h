#ifndef VARMAP_H
#define VARMAP_H
#include "variable.h"
#define VARMAP_MAX_LENGTH 99
class varmap{
public:
	string ka[VARMAP_MAX_LENGTH];
	variable* va[VARMAP_MAX_LENGTH] = {0};
	int size=0;
	varmap();
	void insert(string,float);
	void insert(string,string);
	void insert(string,string*,int );
	void insert_copy(string, string);
	variable* at(string);
	bool exsit(string);
	void print(string);
	~varmap();
};
#endif
