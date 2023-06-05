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
    int i = func(10);
    printf("In main printing return value of test: %d\n", i);
	return 0;
}