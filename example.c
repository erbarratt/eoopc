#include "eOOPc.h"
#include "class.h"

int main (void){
		
	//instantiate object (i.e. new)
		eNEW(Class_t, object);
		
		int i = object->prop1;
		
		//eGET(object, prop2);
	
		//eSET(object, prop2, 4);
	
	//return a value from method, casting to int
		//int i = eMETH(object, method, int, 4);
		
	//calling private method, produces warning
		//eMETH(object, method2);
	
	//getting / setting pprivate property
		//int z = eGET(object, prop1, int);
		//eSET(object, prop1, 4);

	//another object of same class
		//eNEW(Class_t, object2, 1, 2);
		//eMETH(object2, method, int, 4);
		//eMETH(object2, method2, void);

	//use macro as argument
		//printf("%d\n", eGET(object, prop2, int));
		
	//heap version
		//eNEW_H(Class_t, object3, 3, 4);
		//int f = eGET_H(object3, prop1, int);
		//eSET_H(object3, prop1, 44);
		//eMETH_H(object3, method, int, 66);
		//printf("%d\n", eGET_H(object3, prop1, int));
		//eDESTROY_H(object3);
		
	return 0;

}

