%{
   /* definition */
/*   #include <stdio.h>
   #include <ctype.h>
   using namespace std;
   #include <iostream>
   #include <string>
   #include <map>*/
  
   #include "lex.yy.c"
   varmap varm;
%}
%token ID,INT,REAL,STRING_LITERAL


%%
Start : prompt Lines
      ;
Lines : Lines  stat '\n' prompt
      | Lines  '\n' prompt
      | 
      | error '\n' {yyerrok;}
      ;
prompt : {cout << "miniPy> ";}
       ;
stat  : assignExpr
      ;
assignExpr:
        atom_expr '=' assignExpr{
		//add method assign combining insert and change
		varm.assign($1,$2.val);//函数内根据isleft isid isslice 选择操作
		delete $2.val;
		}
      | add_expr {
	  $1.val->print();
	  delete $1.val;
	  }
      ;
number : INT{
$$.val=new variable($1.val);
delete $1.val;
}
       | REAL{
	   $$.val=new variable($1.val);
delete $1.val;
	   }
       ;
factor : '+' factor{
		//add method op_pos
		$$.val=$2.val->op_pos;
		delete $2.val;
}
       | '-' factor{
	   	//add method op_neg
		$$.val=$2.val->op_neg;
		delete $2.val;
	   }
       | atom_expr{
	   $$.val=$1.val;
	   }
       ; 
atom  : ID  {$$.isid=true;$$.isleft=true;$$.isslice=false;
$$.val=varm.at($1.id)}
      | STRING_LITERAL {$$.val=$1.val;
				$$.isleft=false;
			}

      | List {$$.val=$1.val;
			$$.isleft=false;
			}
      | number {$$.val=$1.val;
	        $$.isleft=false;
			}
      ;
slice_op :  /*  empty production */{//默认步长为1
			$$=new variable(1.0);
}
        | ':' add_expr {
		$$.val=$2.val;
		}
        ;
sub_expr:  /*  empty production */
        | add_expr{$$.val=$1.val}
        ;        
atom_expr : atom {$$.isid=$1.isid;$$.isleft=$1.isleft;$$.isslice=$1.isslice;}
        | atom_expr  '[' sub_expr  ':' sub_expr  slice_op ']'{
				$$.isid=false;$$.isleft=true;$$.isslice=true;
			$$.val=41.val;
			$$.isslice=true;
			$$.beg=$3.var;
			$$.end=$5.var;
			$$.step=$6.var;
		}
        | atom_expr  '[' add_expr ']'{
			$$.isid=false;$$.isleft=true;$$.isslice=false;
			$$.val=$2->at($2.val);
		}
        | atom_expr  '.' attrname  {
	$$.isid=false;$$.isleft=true;$$.isslice=false;
		$$.var=$1.atattr($3.id)}
		
		
        | function_name  '(' arglist opt_comma ')'{//所有参数被转化成一个list类的variable*
		$$.isleft=false;
			$$.val=applyfun($1.id,$3.val->merge($4.val));
		}
        |  function_name '('  ')'{
		$$.isleft=false;
			variable* pv;
			pv=new varibale();
			$$.val=applyfun(pv);// 无参数函数
			delete pv;
		
		}
		|atom_expr  '.'  function_name  '(' arglist opt_comma ')'{
		$$.isleft=false;
			$$.val=applyfun($1.id,$1.val->merge($5.val)->merge($6.val));//传入this指针
		}
		|atom_expr  '.'  function_name'(' ')'{
		$$.isleft=false;
			$$.val=applyfun($1.id,$1.val);
		}
        ;
function_name:"append"
			|"range"
			|"print"
			|"len"
			|"list"
		
		
arglist : add_expr {
			$$.val=new varibale(&($1.val),1);// 创建一个单参数的参数列表
			delete $1.val;
	  }
        | arglist ',' add_expr {
		$$.val=$1.val->merge($3.val);  //添加merge
			delete $1.val;
			delete $3.val;
		}
        ;
        ;      
List  : '[' ']' {
			variable* pv;
			pv=new varibale();
			$$.val=new(NULL,1);// 修改构造空list的函数
			delete pv;
				}
      | '[' List_items opt_comma ']'{
			$$.val=$1.val->merge($2.val);
			delete $1.val;
			delete $2.val;
	  } 
      ;
opt_comma : /*  empty production */{
			$$.val=new variable();
           }
          | ','{variable* pv;
			pv=new varibale();
			$$.val=new(NULL,1);// 修改构造空list的函数
			delete pv;
			}
          ;
List_items  
      : add_expr  {
			$$.val=new varibale(&($1.val),1);// 修改构造空list的函数
			delete $1.val;
	  }
      | List_items ',' add_expr{
			$$.val=$1.val->merge($3.val);  //添加merge
			delete $1.val;
			delete $3.val;
	  } 
      ;
add_expr : add_expr '+' mul_expr  {//添加add
				$$.val=$1.val->add($3.val);
			delete $1.val;
			delete $3.val;
			}
	      |  add_expr '-' mul_expr {//添加sub
			$$.val=$1.val->sub($3.val);
			delete $1.val;
			delete $3.val;
		  }
	      |  mul_expr {
		  $$.val=$1.val;
		  }
        ;
mul_expr : mul_expr '*' factor{ //add method mul
	$$.val=$1.val->mul($3.val);
			delete $1.val;
			delete $3.val;
}
        |  mul_expr '/' factor{//add method div
			$$.val=$1.val->div($3.val);
			delete $1.val;
			delete $3.val;
		}
	      |  mul_expr '%' factor{//add method mod
		  	$$.val=$1.val->mod($3.val);
			delete $1.val;
			delete $3.val;
		  }
        |  factor{
		  $$.val=$1.val;
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
