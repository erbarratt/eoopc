#include "eOOPc.h"
#include "class.h"


//PRIVATE DECLARAION

typedef struct{

	ePROP_DEC(int, prop1);
	
	ePRIV_PROP_DEC_PRIV(int, prop2, get);

	int (*method1)(void * eOBJ);

} Class_t;

//PRIVATE METHODS


//PUBLIC METHODS TO OVERRIDE DECLARATIONS

void Class_t_instantiate(void * eOBJ){

	eSELF(Class_t);

	ePROP_DEF(prop1, 3);
	
	ePRIV_PROP_DEF(Class_t, prop2, 4, get);
	
	self->method1 = &Class_t_method1;

}

ePRIV_PROP_FUNC_DEF(Class_t, int, prop2, get)

int Class_t_method1(void * eOBJ){

	eSELF(Class_t);
	
	return eGET(self, prop2);

}

