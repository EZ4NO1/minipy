#ifndef VARIABLE_H
#define VARIABLE_H
#include <iostream>
#include <string>
#define TYPE_INT 0
#define TYPE_FLOAT 1
#define TYPE_STR 2
#define TYPE_LIST 3
#define TYPE_FUN 4
#define TYPE_NONE 5
#define TYPE_LEFT 6
#define TYPE_LEFTLIST 7
#define TYPE_LEFTSTR 8
#define SLEN 100
using namespace std;
class variable {
public:
	int type = 4;
	void* value = 0;
	//bool naint = true;//not a int
	bool anony = true;
	int size = 0;
public:
	variable();
	variable(float,bool=true);
	variable(int, bool=true);
	variable(string,bool=true);
	variable(variable**, int,bool=true);
	variable(variable*,bool=true);
	variable(variable**);//left-type ONLY
	variable(variable***,int);//left-list-type ONLY
        variable(char*[SLEN],int );
	void print(bool b = true);
	~variable();
	static void deleteannoy(variable*);
	static variable* add(variable*, variable*);
	static variable* sub(variable*, variable*);
	static variable* mul(variable*, variable*);
	static variable* div(variable*, variable*);
	static variable* mod(variable*, variable*);
	static variable* at(variable*, variable*);
	static variable* slice(variable*, variable*,variable*, variable*);
	static variable* leftat(variable*, variable*);
	static variable* leftslice(variable*, variable*,variable*, variable*);
	static variable* posop(variable*);
	static variable* negop(variable*);
};
#endif

