extern void print(int);
extern int read();

int func(int i){
	int b;
	
	while (b < i){
		int a;
		a = 10 + b;
		b = b * i;
	}

	while (b < i){
		b = a * 10;
	}
}
