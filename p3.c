extern void print(int);
extern int read();

int func(int i){
	int a;
	int b;
	
	while (b < i){
		int a;
		a = 10 + b;
		b = b * i;
	}

	while (b < i){
		int a;
		b = b * 10;
	}
}
