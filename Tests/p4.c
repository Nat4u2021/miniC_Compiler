extern int read();
extern void print(int);

int func(int n){
	int max;
	int i;
	int a;
	i = 0;
	
	while (i < n){ 
		a = read();
		if (a > max)
			max = a;
		i = i + 1;
	}
	
	return max;
}
