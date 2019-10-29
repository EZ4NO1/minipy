%{
#include "y.tab.h"
#include "varmap.h"
extern struct{
	variable* var;
	string id;
	bool isleft;//能否为左值  仅为true时isid isslice有效
	bool isid;
	bool isslice;
	variable* beg;
	variable* end;
	variable* step;//slice的三个参数
	
} yylval;

/*  any C declaration  */
%}

letter    [a-zA-Z]

digit     [0-9]

number   {digit}+

id       {letter}({letter}|{digit})*

real     {number}'.'{number}?|{number}?'.'{number}

%%
[ \t]+      {/*do nothing , just skip */}
{number}    { 
				int n;
				n=0;
				for(int i=0;i<yyleng;i++){
				n=n*10+(yytext[i]-'0');
				}
				yylval.val=new variable(float(n));
				return INT;
            }
{real}      {
				float n;
				float fl;
				int sig;
				n=0;
				fl=0.1;
				for (int i=0;i<yyleng;i++){
				if (yytext[i]=='.')
					sig=i;
					break;
				}
				for(int i=0;i<sig;i++){
					n=n*10+(yytext[i]-'0');
				}
				for(int i=sig+1;i<yyleng;i++){
					n=n+fl*(yytext[i]-'0');;
					fl=fl/10;
				}
				yylval.val=new variable(n);
                return REAL;
            }
{id}        {
			    yylval.id=yytext;
                return ID; 
            }
\"(\\.|[^\\"])*\"	{
					cahr chs[99];
					string str1;
					(for i=1;i<yyleng;i++){
						chs[i-1]=yytext[i];
					}
					chs[yyleng-1]=0;
					str1=chs;
					yylval.val=new variable(str1);
					return(STRING_LITERAL); /*comments */
					}
.|\n        { return yylval = yytext[0];}
%%
