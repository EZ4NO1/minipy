#include "variable.h"

string type_str[9]={"int","float","str","list","fun","None","left","leftlist","leftstr"};
variable::variable(){
	this->anony = false;
	type=TYPE_NONE;
	value=NULL;
	this->size = 1;
}
variable::variable(float n, bool anonymous ) {
	this->type = TYPE_FLOAT;
	this->anony = anonymous;
	this->value = new float(n);
}

variable::variable(int n, bool anonymous ) {
	this->type = TYPE_INT;
	this->anony = anonymous;
	this->value = new int(n);
}
variable::variable(string str, bool anonymous ){
	this->type=TYPE_STR;
	this->anony = anonymous;
	this->value=new string(str);
	this->size = 0;
}
variable::variable(char* str[SLEN],int n){
	this->type=TYPE_LEFTSTR;
	this->anony = true;
	this->value=new char*[SLEN];
	this->size = n;
        for(int i=0;i<n;i++)
            ((char**)this->value)[i]=str[i];
}
variable::variable(variable *var, bool anonymous ) {
	this->type = var->type;
	this->anony = anonymous;
	if (this->type == TYPE_INT)
			this->value = new int(*((int*)var->value));
	else if (this->type==TYPE_FLOAT)
			this->value = new float(*((float*)var->value));
	else this->value = var->value;
	size = var->size;
}
variable::variable(variable** add){
	this->type=TYPE_LEFT;
	this->anony=true;
	this->value=add;
}

variable::variable(variable*** add,int n){
	this->type=TYPE_LEFTLIST;
	this->anony=true;
	this->size=n;
	this->value=add;
}


variable::variable(variable **a,int n,bool anonymous){
	this->type=TYPE_LIST;
	this->size=n;
	this->anony = anonymous;
	this->value = a;
}
void  variable::print(bool b) {
if(this==0) {cout<<"error print"<<endl; return;}
	if (this->type==TYPE_FLOAT)
			cout<<*((float*)this->value);
		else if (this->type==TYPE_INT)
			cout<<*((int*)this->value);
	else if (this->type==TYPE_STR)
		cout<<'"'<<*((string*)this->value)<<'"';
	else if (this->type==TYPE_LIST){
		cout<<"[";
			if (size!=0){
				if (((variable**)value)[0] == this) cout<<"[...]";
				else(*(variable**)value)->print(false);
			for (int i = 1; i < size ; i++){
				cout<<",";
				if (((variable**)value)[i] == this) cout<<"[...]";
				else(*((variable**)value+i))->print(false);
			}
		}
		cout<<"]";
	}
	else if (this->type==TYPE_NONE){
		cout<<"None";
	}
	if (b) cout<<endl;
}
variable::~variable(){
	//cout << type<<"variable deconstructor start" << endl;
	//print();
	if (type==TYPE_FLOAT)
			delete((float*)value);
		else if (type==TYPE_INT)
			delete((int*)value);
}

void variable::deleteannoy(variable* var) {
	if (var->anony)
		delete var;
}

void typeprint(int type){
    putchar('\'');
    if(type==TYPE_INT)printf("int");
    else if(type==TYPE_FLOAT)printf("float");
    else if(type==TYPE_LIST)printf("list");
    else printf("string");
    putchar('\'');
}

void typeprint2(int type){
    if(type==TYPE_INT)printf("int");
    else if(type==TYPE_FLOAT)printf("float");
    else if(type==TYPE_LIST)printf("list");
    else printf("string");
}

variable* variable::add(variable* var1, variable* var2) {
        if((var1==0)||(var2==0))return 0;
	if (((var1->type == TYPE_INT)||(var1->type == TYPE_FLOAT)) && ((var2->type == TYPE_INT) || (var2->type == TYPE_FLOAT))) {
		if ((var1->type==TYPE_INT) && (var2->type==TYPE_INT)) {
			//cout<<"int"<<*((int*)(var1->value)) + *((int*)(var2->value));
			return new variable(*((int*)(var1->value)) + *((int*)(var2->value)));
		}
		else {
			float f1, f2;
			if (var1->type==TYPE_FLOAT)
				f1 = (float)(*(float*)(var1->value));
			else
				f1 = (float)(*(int*)(var1->value));
			if (var2->type == TYPE_FLOAT)
				f2 = (float)(*(float*)(var2->value));
			else
				f2 = (float)(*(int*)(var2->value));
			return new variable(f1 + f2);
		}
	}
	if ((var1->type == TYPE_LIST) && (var2->type == TYPE_LIST)) {
		variable **l = new variable * [var1->size + var2->size];
		variable** l1 = (variable**)var1->value;
		variable** l2= (variable**) var2->value;
		for (int i = 0; i < var1->size; i++) {
			l[i] = l1[i];
		}
		for (int i = 0; i < var2->size; i++) {
			l[var1->size + i] = l2[i];
		}
		return new variable(l, var1->size + var2->size);
	}
	if ((var1->type == TYPE_STR) && (var2->type == TYPE_STR)) {
		return new variable(*((string*)(var1->value)) + *((string*)(var2->value)));
	}
        printf("TypeError: unsupported operand type(s) for +:");
        typeprint(var1->type);
        printf("and");
        typeprint(var2->type);
        putchar('\n');
        return 0;
}

variable* variable::sub(variable* var1, variable* var2)
{
        if((var1==0)||(var2==0))return 0;
	if (((var1->type == TYPE_INT) || (var1->type == TYPE_FLOAT)) && ((var2->type == TYPE_INT) || (var2->type == TYPE_FLOAT))) {
		if ((var1->type == TYPE_INT) && (var2->type == TYPE_INT)) {
			return new variable(*((int*)(var1->value)) - *((int*)(var2->value)));
		}
		else {
			float f1, f2;
			if (var1->type == TYPE_FLOAT)
				f1 = (float)(*(float*)(var1->value));
			else
				f1 = (float)(*(int*)(var1->value));
			if (var2->type == TYPE_FLOAT)
				f2 = (float)(*(float*)(var2->value));
			else
				f2 = (float)(*(int*)(var2->value));
			return new variable(f1 - f2);
		}
	}
        printf("TypeError: unsupported operand type(s) for -:");
        typeprint(var1->type);
        printf("and");
        typeprint(var2->type);
        putchar('\n');
        return 0;
}

variable* variable::mul(variable* var1, variable* var2) {
        if((var1==0)||(var2==0))return 0;
	if (((var1->type == TYPE_INT) || (var1->type == TYPE_FLOAT)) && ((var2->type == TYPE_INT) || (var2->type == TYPE_FLOAT))) {
		if ((var1->type == TYPE_INT) && (var2->type == TYPE_INT)) {
			return new variable(*((int*)(var1->value)) * *((int*)(var2->value)));
		}
		else {
			float f1, f2;
			if (var1->type == TYPE_FLOAT)
				f1 = (float)(*(float*)(var1->value));
			else
				f1 = (float)(*(int*)(var1->value));
			if (var2->type == TYPE_FLOAT)
				f2 = (float)(*(float*)(var2->value));
			else
				f2 = (float)(*(int*)(var2->value));
			return new variable(f1 * f2);
		}
	}
	if ((var1->type == TYPE_LIST) && (var2->type == TYPE_INT)) {
		variable** l = new variable * [var1->size*(*(int*)var2->value)];
		variable** l1 = (variable**)var1->value;
		for (int i = 0; i < *(int*)var2->value; i++) {
			for (int j = 0; j < var1->size; j++) {
				l[i * var1->size + j] = l1[j];
			}
		}
		return new variable(l, var1->size * (*(int*)var2->value));
	}
	if ((var1->type == TYPE_STR) && (var2->type == TYPE_INT)) {
		string tep;
		tep = "";
		for (int i = 0; i < *(int*)var2->value; i++) {
			tep = tep + *(string*)var1->value;
		}
		return new variable(tep);
	}
        printf("TypeError: unsupported operand type(s) for *:");
        typeprint(var1->type);
        printf("and");
        typeprint(var2->type);
        putchar('\n');
        return 0;
}
variable* variable::div(variable* var1, variable* var2)
{
	float f1, f2;
        if((var1==0)||(var2==0))return 0;
	if ((var1->type == TYPE_INT) && (var2->type == TYPE_INT)){
               f2 = (int)(*(int*)(var2->value));
               if(f2==0){
                   cout<<"ZeroDivisionError: integer division of modulo by zero"<<endl;
                   return 0;
               }
               f1 = (int)(*(int*)(var1->value));
               return new variable(f1/f2);
        }
	if ((var1->type == TYPE_INT)&&(var2->type == TYPE_FLOAT)){
	       f2 = (float)(*(float*)(var2->value));
               if(f2<0.00001){
                    cout<<"ZeroDivisionError: float division by zero"<<endl;
                    return 0;
               }
               f1 = (float)(*(int*)(var1->value));
               return new variable(f1/f2);
        }
	if ((var1->type == TYPE_FLOAT)&&(var2->type == TYPE_INT)){
	       f2 = (float)(*(int*)(var2->value));
               if(f2<0.00001){
                    cout<<"ZeroDivisionError: float division by zero"<<endl;
                    return 0;
               }
               f1 = (float)(*(float*)(var1->value));
               return new variable(f1/f2);
        }
	if ((var1->type == TYPE_FLOAT)&&(var2->type == TYPE_FLOAT)){
	       f2 = (float)(*(float*)(var2->value));
               if(f2<0.00001){
                    cout<<"ZeroDivisionError: float division by zero"<<endl;
                    return 0;
               }
               f1 = (float)(*(float*)(var1->value));
               return new variable(f1/f2);
        }
        printf("TypeError: unsupported operand type(s) for /:");
        typeprint(var1->type);
        printf("and");
        typeprint(var2->type);
        putchar('\n');
        return 0;
}

variable* variable::mod(variable* var1, variable* var2)
{   
        float f1,f2;
        int t1,t2;
        if((var1==0)||(var2==0))return 0;
	if ((var1->type == TYPE_INT) && (var2->type == TYPE_INT)){
               t2 = (int)(*(int*)(var2->value));
               if(t2==0){
                   cout<<"ZeroDivisionError: integer division of modulo by zero"<<endl;
                   return 0;
               }
               t1 = (int)(*(int*)(var1->value));
               return new variable(t1%t2);
        }
	if ((var1->type == TYPE_INT)&&(var2->type == TYPE_FLOAT)){
	       f2 = (float)(*(float*)(var2->value));
               if(f2<0.00001){
                    cout<<"ZeroDivisionError: float modulo"<<endl;
                    return 0;
               }
               f1 = (float)(*(int*)(var1->value));
               return new variable(f1-((int)(f1/f2))*f2);
        }
	if ((var1->type == TYPE_FLOAT)&&(var2->type == TYPE_INT)){
	       f2 = (float)(*(int*)(var2->value));
               if(f2<0.00001){
                    cout<<"ZeroDivisionError: float modulo"<<endl;
                    return 0;
               }
               f1 = (float)(*(float*)(var1->value));
               return new variable(f1-((int)(f1/f2))*f2);
        }
	if ((var1->type == TYPE_FLOAT)&&(var2->type == TYPE_FLOAT)){
	       f2 = (float)(*(float*)(var2->value));
               if(f2<0.00001){
                    cout<<"ZeroDivisionError: float modulo"<<endl;
                    return 0;
               }
               f1 = (float)(*(float*)(var1->value));
               return new variable(f1-((int)(f1/f2))*f2);
        }
        printf("TypeError: unsupported operand type(s) for %:");
        typeprint(var1->type);
        printf("and");
        typeprint(var2->type);
        putchar('\n');
        return 0;
}

variable* variable::at(variable* var1, variable* var2) {
        string h="a";
        if((var1==0)||(var2==0))return 0;
	if (var1->type == TYPE_LIST) {
            if(var2->type == TYPE_INT){
		if ((*(int*)var2->value >=0)&& (*(int*)var2->value < var1->size)) {
			return ((variable**)var1->value)[*(int*)var2->value];
		}
		else{
			cout<<"out-of-index exception"<<endl;
			return 0;
		}
            }
            else{
                cout<<"TypeError: list indices must be integers,not ";
                typeprint2(var2->type);
                cout<<endl;
                return 0;
            }
	}
	if(var1->type == TYPE_STR) {
            if(var2->type == TYPE_INT) {
		if ((*(int*)var2->value >=0)&& (*(int*)var2->value < (*(string*)var1->value).size() )) {    
                        h[0]=(char)(*(string*)var1->value).at(*(int*)var2->value);
			return new variable(h);
		}
		else{
			cout<<"out-of-index exception"<<endl;
			return 0;
		}
            }
            else{
                cout<<"TypeError: string indices must be integers,not ";
                typeprint2(var2->type);
                cout<<endl;
                return 0;
            }            
	}
        cout<<"TypeError: ";
        typeprint(var1->type);
	cout<<" object has no attribute \'__getitem__\'"<<endl;
        return 0;
}


variable* variable::leftat(variable* var1, variable* var2) {
        if((var1==0)||(var2==0))return 0;
	if (var1->type == TYPE_LIST){ 
           if(var2->type == TYPE_INT) {
		if ((*(int*)var2->value >=0)&& (*(int*)var2->value < var1->size)) {
			return new variable (&((variable**)var1->value)[*(int*)var2->value]);
		}
		else{
			cout<<"out-of-index exception"<<endl;
			return 0;
		}
           }
           else{
                cout<<"TypeError: list indices must be integers,not ";
                typeprint2(var2->type);
                cout<<endl;
                return 0;
            }
	}
	if(var1->type == TYPE_STR) {
            if(var2->type == TYPE_INT) {
		if ((*(int*)var2->value >=0)&& (*(int*)var2->value < (*(string*)var1->value).size() )) {    
                        char* l[SLEN];
                        l[0]=&(*(string*)var1->value).at(*(int*)var2->value);
			return new variable(l,1);
		}
		else{
			cout<<"out-of-index exception"<<endl;
			return 0;
		}
            }
            else{
                cout<<"TypeError: string indices must be integers,not ";
                typeprint2(var2->type);
                cout<<endl;
                return 0;
            }            
	}
        cout<<"TypeError: ";
        typeprint(var1->type);
	cout<<" object has no attribute \'__getitem__\'"<<endl;
        return 0;
}

variable* variable::slice(variable* var1, variable* var2,variable* var3,variable* var4) {
        if((var1==0)||(var2==0)||(var3==0)||(var4==0))return 0;
	if (var1->type == TYPE_LIST){
           if(((var2->type == TYPE_INT)||(var2->type == TYPE_NONE)) && ((var3->type == TYPE_INT) || (var3->type == TYPE_NONE))&&(var4->type==TYPE_INT) ){
		int numl;
		int numh;	
		int step ;
		step= *((int*)(var4->value));
	if (step == 0) {
                cout<<"ValueError: slice step cannot be zero"<<endl;
		return 0;
	}
	if (var2->type == TYPE_NONE) {
			if (step > 0)
				numl = 0;
			else
				numl =var1->size-1;
		}
		else {
			numl = *(int*)var2->value;
			if (numl>var1->size-1) numl=var1->size-1;
			if (numl<-var1->size) numl=0;
			if (numl<0) numl=numl+var1->size;

		}

		if (var3->type == TYPE_NONE) {
			if (step > 0)
				numh = var1->size;
			else
				numh =-1;
		}
		else {
			numh=*(int*)var3->value;
			if (numh>var1->size) numh=var1->size;
			if(numh<-var1->size-1) numh=-1;
			if (numh<0) numh=numh+var1->size;

		}
		//cout<<numl<<","<<numh<<"s"<<step<<endl;
		
		if ((numh - numl) * step <= 0) {
			variable** t = 0;
			return new variable(t, 0);
		}
		int count = 0;
		int tep = numl;
		while (((numh - tep) * step > 0)&&(count>=0)&&(count<var1->size)) {
			tep += step;
			count++;
		}
		variable** l = new variable * [count];
		for (int i = 0; i < count; i++) {
			l[i] = ((variable**)var1->value)[numl + i * step];
		}
		return new variable(l, count);
            }
            else {
                  cout<<"TypeError:slice indices must be integers or None or have an __index__ method"<<endl;
                  return 0;
            }
	}


	if (var1->type == TYPE_STR){
           if(((var2->type == TYPE_INT)||(var2->type == TYPE_NONE)) && ((var3->type == TYPE_INT) || (var3->type == TYPE_NONE))&&(var4->type==TYPE_INT) ){
                int size;
		int numl;
		int numh;	
		int step ;
                size=(*(string*)var1->value).size();
		step= *((int*)(var4->value));
	if (step == 0) {
                cout<<"ValueError: slice step cannot be zero"<<endl;
		return 0;
	}
	if (var2->type == TYPE_NONE) {
			if (step > 0)
				numl = 0;
			else
				numl =size-1;
		}
		else {
			numl = *(int*)var2->value;
			if (numl>size-1) numl=size-1;
			if (numl<-size) numl=0;
			if (numl<0) numl=numl+size;

		}

		if (var3->type == TYPE_NONE) {
			if (step > 0)
				numh = size;
			else
				numh =-1;
		}
		else {
			numh=*(int*)var3->value;
			if (numh>size) numh=size;
			if(numh<-size-1) numh=-1;
			if (numh<0) numh=numh+size;

		}
		//cout<<numl<<","<<numh<<"s"<<step<<endl;
		
		if ((numh - numl) * step <= 0) {
			string t = "";
			return new variable(t);
		}
		int count = 0;
		int tep = numl;
		while (((numh - tep) * step > 0)&&(count>=0)&&(count<size)) {
			tep += step;
			count++;
		}
		string l(count,'a');
		for (int i = 0; i < count; i++) {
			l[i] = (*(string*)var1->value)[numl + i * step];
		}
		return new variable(l);
            }
            else {
                  cout<<"TypeError:slice indices must be integers or None or have an __index__ method"<<endl;
                  return 0;
            }
	}
        cout<<"TypeError: ";
        typeprint(var1->type);
	cout<<" object has no attribute \'__getitem__\'"<<endl;
        return 0;
}

variable* variable::leftslice(variable* var1, variable* var2,variable* var3,variable* var4) {
	if((var1==0)||(var2==0)||(var3==0)||(var4==0))return 0;
        if (var1->type == TYPE_LIST){
            if(((var2->type == TYPE_INT)||(var2->type == TYPE_NONE)) && ((var3->type == TYPE_INT) || (var3->type == TYPE_NONE))&&(var4->type==TYPE_INT)) {
		int numl;
		int numh;	
		int step ;
		step= *((int*)(var4->value));
	if (step == 0) {
		return 0;
	}
	if (var2->type == TYPE_NONE) {
			if (step > 0)
				numl = 0;
			else
				numl =var1->size-1;
		}
		else {
			numl = *(int*)var2->value;
			if (numl>var1->size-1) numl=var1->size-1;
			if (numl<-var1->size) numl=0;
			if (numl<0) numl=numl+var1->size;

		}

		if (var3->type == TYPE_NONE) {
			if (step > 0)
				numh = var1->size;
			else
				numh =-1;
		}
		else {
			numh=*(int*)var3->value;
			if (numh>var1->size) numh=var1->size;
			if(numh<-var1->size-1) numh=-1;
			if (numh<0) numh=numh+var1->size;

		}
		//cout<<numl<<","<<numh<<"s"<<step<<endl;
		
		if ((numh - numl) * step <= 0) {
			return 0;
		}
		int count = 0;
		int tep = numl;
		while ((numh - tep) * step > 0) {
			tep += step;
			count++;
		}
		variable*** l = new variable** [count];
		for (int i = 0; i < count; i++) {
			l[i] = &((variable**)var1->value)[numl + i * step];
		}
		return new variable(l, count);
           }
            else {
                  cout<<"TypeError:slice indices must be integers or None or have an __index__ method"<<endl;
                  return 0;
            }
	}

	if (var1->type == TYPE_STR){
           if(((var2->type == TYPE_INT)||(var2->type == TYPE_NONE)) && ((var3->type == TYPE_INT) || (var3->type == TYPE_NONE))&&(var4->type==TYPE_INT) ){
                int size;
		int numl;
		int numh;	
		int step ;
                size=(*(string*)var1->value).size();
		step= *((int*)(var4->value));
	if (step == 0) {
                cout<<"ValueError: slice step cannot be zero"<<endl;
		return 0;
	}
	if (var2->type == TYPE_NONE) {
			if (step > 0)
				numl = 0;
			else
				numl =size-1;
		}
		else {
			numl = *(int*)var2->value;
			if (numl>size-1) numl=size-1;
			if (numl<-size) numl=0;
			if (numl<0) numl=numl+size;

		}

		if (var3->type == TYPE_NONE) {
			if (step > 0)
				numh = size;
			else
				numh =-1;
		}
		else {
			numh=*(int*)var3->value;
			if (numh>size) numh=size;
			if(numh<-size-1) numh=-1;
			if (numh<0) numh=numh+size;

		}
		//cout<<numl<<","<<numh<<"s"<<step<<endl;
		
		if ((numh - numl) * step <= 0) {
			char* l[SLEN];
			return new variable(l,0);
		}
		int count = 0;
		int tep = numl;
		while (((numh - tep) * step > 0)&&(count>=0)&&(count<size)) {
			tep += step;
			count++;
		}
		char* l[SLEN];
		for (int i = 0; i < count; i++) {
			l[i] = &(*(string*)var1->value)[numl + i * step];
		}
		return new variable(l,count);
            }
            else {
                  cout<<"TypeError:slice indices must be integers or None or have an __index__ method"<<endl;
                  return 0;
            }
	}

        cout<<"TypeError: ";
        typeprint(var1->type);
	cout<<" object has no attribute \'__getitem__\'"<<endl;
        return 0;
}


variable* variable::posop(variable* var)
{       if(var==0)return 0;
	if (var->type == TYPE_INT) {
		return new variable(*(int*)var->value);
	}
	if (var->type == TYPE_FLOAT) {
		return new variable(*(float*)var->value);
	}
        cout<<"TypeErrror: bad operand type for unary +:";
        typeprint(var->type);
        cout<<endl;
        return 0;
}
variable* variable::negop(variable* var)
{       if(var==0)return 0;
	if (var->type == TYPE_INT) {
		return new variable(-*(int*)var->value);
	}
	if (var->type == TYPE_FLOAT) {
		return new variable(-*(float*)var->value);
	}
        cout<<"TypeErrror: bad operand type for unary -:";
        typeprint(var->type);
        cout<<endl;
        return 0;
}
