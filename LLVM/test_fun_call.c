extern int read();
extern void print(int);

int func(int i){
	int a;
	int b;
	a = read();
	b = a + i;
	print(a);	
	return (a+b);	
}
