#include "varmap.h"

varmap::varmap()
{	
	this->size = 0;
}


void varmap::insert_assign(variable* var1, variable* var2)
{
        if(var2==0){var1=0;return;}
	string key1 = string(*(string*)var1->value);
	for (int i = 0; i < size; i++) {
		if (key[i] == key1) {
			if ((var2->type==TYPE_INT)||(var2->type==TYPE_FLOAT))
			pointer[i] = new variable( var2);
			else pointer[i]=var2;
			return;
		}
	}
	key[size] = string(*(string*)var1->value);
	if ((var2->type==TYPE_INT)||(var2->type==TYPE_FLOAT))
	pointer[size] = new variable( var2);
	else pointer[size]=var2;
	size++;
}

variable* varmap::at(variable* var)
{
	string key1 = string(*(string*)var->value);
	for (int i = 0; i < size; i++) {
		if (key[i] == key1)
			return pointer[i];
	}
        cout<<"NameError:name \'"<<*(string*)var->value<<"\' is not defined"<<endl;
	return 0;
}
variable* varmap::leftat(variable* var)
{
	string key1 = string(*(string*)var->value);
        if(var==0)return 0;
	for (int i = 0; i < size; i++) {
		if (key[i] == key1)
			return new variable(&pointer[i]);
	}
	return 0;
}


bool varmap::exsit(variable* var)
{
	string key1 = string(*(string*)var->value);
        if(var==0)return false;
	for (int i = 0; i < size; i++) {
		if (key[i] == key1)
			return true;
	}
	return false;
}

variable* varmap::func(variable* var1, variable* var2){//参数被打包成了list
	if ((var1==0)||(var2==0)) return 0;
	string funcname=*(string*)var1->value;
	if (funcname=="len"){
		if (var2->size==1){
			variable* list=((variable**)var2->value)[0];
			if (list->type==TYPE_LIST)return new variable(list->size);
			else {cout<<"NameError:object of type"<<"\""<<type_str[list->type]<<"\""<<"has no"<<"len()"<<endl; return 0;}
			}
		
	else {cout<<"TypeError:len() takes exactly one argument("<<var2->size<<" given)"; return 0;}
	}
	if (funcname=="range"){
		if (var2->size==1){
			variable* num=((variable**)var2->value)[0];
			if (num->type==TYPE_INT){
				int n=*(int*)num->value;
				variable** l=new variable*[n];
			for (int i=0;i<n ;i++){
				l[i]=new variable(i);
			}
			return new variable(l,n);
			}
			else 
			{cout<<"NameError:object of type"<<"\""<<type_str[num->type]<<"\""<<"has no"<<"range()"<<endl; return 0;}

		}else {cout<<"TypeError:range() takes exactly one argument("<<var2->size<<" given)"; return 0;}
	}
	if (funcname=="print"){
		if (var2->size==1){
			variable* var=((variable**)var2->value)[0];
			var->print();
			return 0;
		}else{ cout<<"TypeError:print() takes exactly one argument("<<var2->size<<" given)";return 0;}
	}
	if (funcname=="exit"){
		if(var2->size==0){
			exit(0);
		}
		else{ cout<<"TypeError:len() takes exactly one argument("<<var2->size<<" given)";return 0;}
	}
	cout<<"NameError: name\""<<funcname << "\"is not defined"<<endl;
	return 0;
}



variable* varmap::objfunc(variable* var1, variable* var2,variable* var3){
	string funcname=*(string*)var2->value;
        if((var1==0)||(var2==0)||(var3==0))return 0;
	if (var1->type==TYPE_LIST){
		
			if (funcname=="append"){
				if (var3->size==1){
					variable* par=((variable**)var3->value)[0];
						variable** l=new variable*[var1->size+1];
						for (int i=0;i<var1->size;i++){
							l[i]=((variable**)var1->value)[i];
						}
						l[var1->size]=par;
						var1->size++;
						var1->value=l;
				}
			}
		        else {
                            cout<<"AttributeError:\'list\' object has no attribute "<<"\'";
                            cout<<funcname<<"\'"<<endl;
                        }
	}
        if(var1->type==TYPE_INT){
                            cout<<"AttributeError:\'int\' object has no attribute "<<"\'";
                            cout<<funcname<<"\'"<<endl;
                        }
        if(var1->type==TYPE_FLOAT){
                            cout<<"AttributeError:\'float\' object has no attribute "<<"\'";
                            cout<<funcname<<"\'"<<endl;
                        }
        if(var1->type==TYPE_STR){
                            cout<<"AttributeError:\'string\' object has no attribute "<<"\'";
                            cout<<funcname<<"\'"<<endl;
                        }
	return 0;
}
void varmap::assign(variable* var1,variable* var2){
        if((var1==0)||(var2==0))return;
	if (var1->type==TYPE_LEFT){
		if ((var2->type==TYPE_INT)||(var2->type==TYPE_FLOAT))
		*(variable**)(var1->value)=new variable(var2);
		else *(variable**)(var1->value)=var2;
	}
	else if (var1->type==TYPE_LEFTLIST){
		if ((var2->type==TYPE_LIST)&&(var2->size==var1->size)){
			for (int i=0;i<var1->size;i++){
				if((((variable**)var2->value)[i]->type==TYPE_INT)||(((variable**)var2->value)[i]->type==TYPE_FLOAT))
				*(((variable***)var1->value)[i])=new variable(((variable**)var2->value)[i]);
				else *(((variable***)var1->value)[i])=((variable**)var2->value)[i];
		          }
		}
		else{}
	}
        else if(var1->type==TYPE_LEFTSTR){
              if(var2->type==TYPE_STR){
                        for(int i=0;i<var1->size;i++)
                               ((char**)var1->value)[i][0]=(*(string*)var2->value)[i];
              }
              else{}
        }
}
varmap::~varmap()
{
}


