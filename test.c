#include"ast.h"
#include<stdio.h>

int main(){
	vector<astNode*> slist;
	astNode *a11 = createVar("test1");
	astNode *a12 = createVar("test2");
	astNode *a13 = createVar("test3");
	
	astNode *a14 = createBExpr(a11, a12, add);
	astNode *a15 = createAsgn(a13, a14);	
	slist.push_back(a15);
	
	astNode *a21 = createDecl("local");
	slist.push_back(a21);


	astNode *a31 = createVar("test31");
	astNode *a32 = createUExpr(a31, uminus);
	astNode *a33 = createRet(a32);
	slist.push_back(a33);

	astNode *a71 = createCnst(20);
	astNode *a72 = createVar("test4");
	astNode *a73 = createRExpr(a71, a72, ge);


	astNode *a8 = createBlock(&slist);

	astNode *a7 = createFunc("func_name1", NULL, a8);

	printNode(a7);
	
	freeNode(a7);
}
