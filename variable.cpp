#include "variable.h"
variable::variable(){
	type=TYPE_NONE;
	value=NULL;
	naint=true;
	size = 1;
}
variable::variable(float n){
	this->type=TYPE_NUMBER;
	if ((int)n==n){
		naint=false;
		this->value=new int;
		*((int*)this->value)=int(n);
		}
	else{
		naint=true;
		this->value=new float;
		*((float*)this->value)=n;
		}
	size = 1;
}
variable::variable(string str){
	this->type=TYPE_STR;
	this->value=new string(str);
	naint=true;
	size = 1;
}
variable::variable(variable &var) {
	this->type = var.type;
	if (this->type == TYPE_NUMBER)
		if (this->naint)
			this->value = new float(*((float*)var.value));
		else
			this->value = new int(*((int*)var.value));
	else if (this->type == TYPE_STR)
		this->value = new string(*((string*)var.value));
	else if (this->type == TYPE_LIST) {
		value = new variable*[var.size];
		for (int i = 0; i <var.size; i++) {
			*((variable**)(value)+i) = new variable(**((variable**)var.value + i));
		}
	}
	else if (this->type == TYPE_NONE) {
	}
	this->naint = var.naint;
	size = var.size;
}

variable::variable(variable **a,int n){
	this->type=TYPE_LIST;
	this->value=new variable*[n];
	naint=true;
	size = n;
	for (int i = 0; i < n; i++) {
		*((variable**)value + i) = new variable(*a[i]);
	}
}
int variable::print(bool b) {

	if (this->type==TYPE_NUMBER)
		if (this->naint)
			cout<<*((float*)this->value);
		else 
			cout<<*((int*)this->value);
	else if (this->type==TYPE_STR)
		cout<<"\""<<*((string*)this->value)<<"\"";
	else if (this->type==TYPE_LIST){
		cout<<"[";
			if (size!=0){
				(*(variable**)value)->print(false);
			for (int i = 1; i < size ; i++){
				cout<<",";
				(*((variable**)value+i))->print(false);
			}
		}
		cout<<"]";
	}
	else if (this->type==TYPE_NONE){
		cout<<"None";
	}
	else return -1;
	if (b) cout<<endl;
	return 0;
}
variable::~variable(){
	//cout << type<<"variable deconstructor start" << endl;
	//print();
	if (type==TYPE_NUMBER)
		if (naint)
			delete((float*)value);
		else
			delete((int*)value);
	else if (type==TYPE_STR)
		delete((string*)value);
	else if (type == TYPE_LIST) {
		for (int i = 0; i < size; i++) {
			delete(*((variable**)(value)+i));
		}
	}
}
