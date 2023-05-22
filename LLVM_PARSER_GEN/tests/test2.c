extern void print(int);
extern int read();

int func(int i){
	int a;
	int b;
	
	a = 10;
	b = 20;

  if (a < i){
		a = 10 + b;
	}

	if (b > i) 
			b = a;
	
	if (b == a) i = 0;

	return 0;
}
