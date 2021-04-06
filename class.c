//need OOP macros
	#include "eOOPc.h"

//include public declaration
	#include "class.h"

//PRIVATE DECLARAION
	typedef struct{
	
		eDIR_EXTENDS(parent, parent);
	
		//interface
			eIMPLEMENTS(interface);
	
		//matching public prop declaration
			ePROP_DEC(int, prop1);
		
		//private property declaration + PUBLIC function pointer declarations
			ePRIV_PROP_DEC_PRIV(int, prop2, get);
	
		//public method function pointer
			int (*method1)(void * eOBJ);
		
		//private method function pointer
			int (*method2)(void * eOBJ);
	
	} Class_t;

//PRIVATE METHODS
	int Class_t_method2(void * eOBJ){
	
		eSELF(Class_t);
		
		return self->prop1;
	
	}

//PUBLIC METHOD DEFINITIONS TO OVERRIDE DECLARATIONS

	//private property PUBLIC get/set method definitions
		ePRIV_PROP_FUNC_DEF(Class_t, int, prop2, get)
	
	//other public method definitions
		int Class_t_method1(void * eOBJ){
		
			eSELF(Class_t);
			
			return 4;
		
		}

	void Class_t_instantiate(void * eOBJ){
	
		eSELF(Class_t);
		
		ePROP_DEF(prop1, 3);
		
		ePRIV_PROP_DEF(Class_t, prop2, 4, get);
		
		self->method1 = &Class_t_method1;
		self->method2 = &Class_t_method2;
	
	}
	
	

