#include<stdio.h>

extern int func(int);

void print(int n){
	printf("%d\n", n);
}

int read(){
	int n;
	scanf("%d",&n);
	return(n); 
}

int main(){
 int a = func(20);
 printf("%d", a);
}

