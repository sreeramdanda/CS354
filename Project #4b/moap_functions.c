
// for each of the following functions 
// correct the prototype
// write function body
// replace return with the correct return statement
//
// you may write as many helper functions here as you wish

//NO PARAMETERS
int algorithm_1() {
	int a = 8000;
	int b = 63;
	int c = a + b;
    return c;  
}

//GIVEN P1 AND P2
int algorithm_2(int a, int b) {
	if(a >= b){
		int c = a/b;
		return c;
	}
	else{
		int c = a + a;
		return (c + a) + b;
	}
}

int helper_algorithm_3(int a){
	return a - 1;
}

//GIVEN P3 AND P4
int algorithm_3(int a, int b) {
	int d = b;
	int c = 0;
	while (d > 0){
		c += a;
		d = helper_algorithm_3(d);
	}
	return c;
}

//GIVEN P5 AND *p
void algorithm_4(int a, int* p){
	int value = a;

	value = a + a;
	value += a;
	
	*p = value;
}



