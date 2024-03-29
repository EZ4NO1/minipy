
LEX=lex
YACC=yacc
CC=g++
OBJECT=main.out #生成的目标文件
 
$(OBJECT): y.tab.c  y.tab.h variable.cpp variable.h varmap.cpp varmap.h
	$(CC)  y.tab.c variable.cpp varmap.cpp -g -o $(OBJECT)
	./$(OBJECT) #编译后立刻运行
 
y.tab.c y.tab.h: minipy.y lex.yy.c
# bison使用-d参数编译.y文件
	$(YACC) -d minipy.y
 
lex.yy.c: minipy.l
	$(LEX) minipy.l
clean:
	rm lex.yy.c y.tab.c y.tab.h $(OBJECT)
