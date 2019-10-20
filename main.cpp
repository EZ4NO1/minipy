#include "varmap.h"
int main() {
	//variable a(1.0);
	//variable b((float)(2.2));
	//variable c("string");
	//variable v[3] = { a, b, c };
	//variable l(v, 3);
	//a.print();
	//b.print();
	//c.print();
	//l.print();
	//variable v2[4] = { a, b, c ,l};
	//variable l2(v2,4);
	//l2.print();
	varmap vm;
	string strl[3] = { "a","b","c" };
	vm.insert("a", 1.0);
	vm.insert("b", 2.2);
	vm.insert("c", "string");
	vm.insert("d","123");
	vm.print("a");
	vm.print("b");
	vm.print("c");
	vm.print("d");
	vm.insert("e",strl , 3);
	vm.print("e");
	vm.insert("a", 99);
	string str2[5] = { "a","b","c","d" ,"e"};
	vm.insert("f", str2, 5);
	vm.print("f");
	vm.insert_copy("f", "ff");
	vm.print("ff");
	//while (1);
	//v[0]=*pl;
	//v[1]=*pln;
	//v[2]=*pc;
	//variable *pll=new variable(v);
	//pll->print();
	//pln->print();
	//variable *pn=new variable();
	//pn->print();
	//return 0;

}
