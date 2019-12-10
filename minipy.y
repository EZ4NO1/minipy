%{
   /* definition */
/*   #include <stdio.h>
   #include <ctype.h>
   using namespace std;
   #include <iostream>
   #include <string>]
   #include <map>*/
#include "varmap.h"
 #define YYSTYPE variable* 
   #include "lex.yy.c"
   varmap varm;
void yyerror(char*);
%}
%token ID INT REAL STRING_LITERAL


%%
Start : prompt Lines
      ;
Lines : Lines  stat '\n' prompt
      | Lines  '\n' prompt 
      |
      | error '\n'
      ;
prompt : {cout << "miniPy> ";}
       ;
stat  : assignExpr
      |
      ;
assignExpr:
		ID '=' add_expr{
		varm.insert_assign($1,$3);
		}
        |left_expr '=' add_expr{ //add method assign combining insert and change
		varmap::assign($1,$3);
		}
      | add_expr {
	  if ($1!=0) $1->print();
	  }
      ;
	  
left_expr:atom_expr  '[' sub_expr  ':' sub_expr  slice_op ']'{$$=variable::leftslice($1,$3,$5,$6);}
        |  atom_expr '[' add_expr ']'{$$=variable::leftat($1,$3);} 
		;
number : INT{
    $$=$1;
}
       | REAL{
	   $$=$1;
	   }
       ;
factor : '+' factor{
		//add method op_pos
		$$=variable::posop($2);
}
       | '-' factor{
	   	//add method op_neg
		$$=variable::negop($2);
	   }
       | atom_expr
       ; 
atom  : ID  {$$=varm.at($1);}
      | STRING_LITERAL {$$=$1;
		}

      | List {$$=$1;}
      | number {$$=$1;}
      ;


slice_op :  /*  empty production */{$$=new variable(1);}
		|':'{$$=new variable(1);}
        | ':' add_expr {$$=$2;}
        ;
sub_expr:  /*  empty production */{$$=new variable();}
        | add_expr{$$=$1;}
        ;        
atom_expr : atom  {$$=$1;}
        | atom_expr  '[' sub_expr  ':' sub_expr  slice_op ']'{$$=variable::slice($1,$3,$5,$6);}
        | atom_expr  '[' add_expr ']'{$$=variable::at($1,$3);}
		|func_exper
        ;

func_exper: func_name  '(' List_items ')'{
			$$=varmap::func($1,$3);
}
        | func_name   '('  ')'{
				variable* t=new variable();
				t->type=TYPE_LIST;
				t->size=0;
				t->value=0;
				$$=varmap::func($1,t);
		}
        | atom_expr'.'func_name  '(' List_items ')'{
			$$=varmap::objfunc($1,$3,$5);
		}
        | atom_expr'.'func_name   '('  ')'{
			variable* t=new variable();
				t->type=TYPE_LIST;
				t->size=0;
				t->value=0;
			$$=varmap::objfunc($1,$3,t);
		}
		;

func_name:ID{$$=$1;}
;
List  : '[' ']' {
			$$=new variable();
			$$->type=TYPE_LIST;
			$$->size=0;
			$$->value=0;
				}
      | '[' List_items opt_comma ']'{
			$$=$2;
	  } 
      ;
opt_comma : /*  empty production */{}
          | ','{}
          ;
List_items  
      : add_expr  {
			variable** l=new variable*;
			*l=$1;
			$$=new variable(l,1);
	  }
      | List_items ',' add_expr{
	        variable **l = new variable * [$1->size+1];
			for (int i = 0; i < $1->size; i++) {
			l[i] = ((variable**)$1->value)[i];
		}
		l[$1->size]=$3;
		$$=new variable(l,$1->size+1);
	  } 
      ;
add_expr : add_expr '+' mul_expr  {//Ìí¼Óadd
				$$=variable::add($1,$3);
			}
	      |  add_expr '-' mul_expr {//Ìí¼Ósub
			$$=variable::sub($1,$3);
		  }
	      |  mul_expr {
		    $$=$1;
		  }
        ;
mul_expr : mul_expr '*' factor{ //add method mul
           $$=variable::mul($1,$3);
		}
        |  mul_expr '/' factor{//add method div
			$$=variable::div($1,$3);
		}
	      |  mul_expr '%' factor{//add method mod
		  $$=variable::mod($1,$3);
		  }
        |  factor{
		$$=$1;
		}
        ;

%%

int main()
{
   return yyparse();
}

void yyerror(char *s)
{
   cout << s << endl<<"miniPy> "; 
}

int yywrap()
{ return 1; }        		    
