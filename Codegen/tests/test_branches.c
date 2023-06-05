extern int read();
extern void print(int);

int func(int i){
	int a;
	int b;

	if (i > 100){
		a = 10;
		b = 20;
	}
	else{
		a = 100;
		b = 200;
	}
	
	return (i + a);
}

