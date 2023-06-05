extern int read();
extern void print(int);

int func(int i){
	int a;
	int b;
	int c;

	a = 10;
	c = a + 1;
	
	if (c < 100){
		b = a + 100;
	}
	else {
		b = a + 20;
	}

	return b;
}
