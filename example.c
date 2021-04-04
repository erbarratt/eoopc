#include "eOOP.h"

//would be in header of it's own//////////
	typedef struct{
		
			eACCESS prop1_access;
			int prop1;
			
			eACCESS prop2_access;
			int prop2;
			
			eACCESS method_access;
			int (* method)(void * eOBJ, int something);
			
			eACCESS method2_access;
			void (* method2)(void * eOBJ);
			
		} Class_t;
		
		Class_t Class_t_instantiate(int arg1, int arg2);
		void Class_t_heap_instantiate(Class_t * class, int arg1, int arg2);
		void Class_t_heap_destruct(Class_t * class);
		int class_method(void * eOBJ, int something);
		void class_method2(void * eOBJ);
//////////////////////////////////////////

Class_t Class_t_instantiate(int arg1, int arg2){

	Class_t tmp = {
		.prop1_access = private,    .prop1 = arg1,
		.prop2_access = public,     .prop2 = arg2,
		.method_access = public,    .method = &class_method,
		.method2_access = private,  .method2 = &class_method2
	};
	return tmp;
	
}

void Class_t_heap_instantiate(Class_t * class, int arg1, int arg2){

	//stack or heap allocations
		class->prop1_access = public; class->prop1 = arg1;
		
		class->prop2_access = private; class->prop2 = arg2;
		
		class->method_access = public; class->method = &class_method;
		
		class->method2_access = private; class->method2 = &class_method2;

}

int class_method(void * eOBJ, int something){

	//get self var
		eSELF(Class_t);
	
	//can freely access props as "inside" class within this function
		printf("hellod %d %d %d\n", self->prop1, self->prop2, something);
	
	//call private method from within a public method, again fine
		self->method2(self);
	
	return something;
}

void class_method2(void * eOBJ){

	//get self var
		eSELF(Class_t);
		
	printf("method2\n");
	
	//change public var to show persistence
		self->prop2 = 33;
	
}


int main (void){

	//instantiate object (i.e. new)
		Class_t object = eNEW(Class_t, 1, 2);
	
	//return a value from method, casting to int
		int i = eMETH(object, method, int, 4);
		
	//calling private method, produces warning
		eMETH(object, method2, void);
	
	//getting / setting pprivate property
		//int z = eGET(object, prop1, int);
		eSET(object, prop1, 4);

	//another object of same class
		Class_t object2 = eNEW(Class_t, 1, 2);
		eMETH(object2, method, int, 4);
		eMETH(object2, method2, void);

	//use macro as argument
		printf("%d\n", eGET(object, prop2, int));
		
	//heap version
		Class_t * object3 = eNEW_H(Class_t, object3, 3, 4);
		int f = eGET_H(object3, prop1, int);
		eSET_H(object3, prop1, 44);
		eMETH_H(object3, method, int, 66);
		printf("%d\n", eGET_H(object3, prop1, int));
		eDESTROY_H(object3);
		
	return 0;

}

