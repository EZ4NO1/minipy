#ifndef VARIABLE_H
#define VARIABLE_H
#include <iostream>
#include <string>
#include <vector>
#define TYPE_NUMBER 0 
#define TYPE_STR 1
#define TYPE_LIST 2
#define TYPE_FUN 3
#define TYPE_NONE 4
using namespace std;
class variable {
public:
	int type = 4;
	void* value = 0;
	bool naint = true;//not a int
	int size = 0;
public:
	variable();
	variable(float);
	variable(string);
	variable(variable**, int);
	variable(variable&);
	int print(bool b = true);
	~variable();
};
#endif

