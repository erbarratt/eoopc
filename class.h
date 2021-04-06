#ifndef OOP_CLASS_H
#define OOP_CLASS_H

//interface definitions can contain expressly written variables,
	//other e@ macros etc as needed.
		#define eINTERFACE_interface() \
			int poop; \
			int shmoop
	
		struct parent{
			int pprop1;
			int pprop2;
		};

//PUBLIC DEFINITION AND METHODS
	
	struct Class_t{
	
		//parent for upcasts
			eDIR_EXTENDS(parent, parent);
	
		//interface
			eIMPLEMENTS(interface);
	
		//define a public property
			ePROP_DEC(int, prop1);
			
		//define function pointers for get, set or both for private property
			ePRIV_PROP_DEC_PUB(int, prop2, get);
		
		//public method function pointer
			int (*method1)(void * eOBJ);
		
	};
	
//public class function declarations

	//get and/or set PUBLIC function declarations
		ePRIV_PROP_FUNC_DEC(Class_t, int, prop2, get)
	
	//other defined public methods declarations
		int Class_t_method1(void * eOBJ);

	//always need an instantiate. Void pointer so function can cast back to struct type pointer
	//this means we don't get conflicting type errors
		void Class_t_instantiate(void * eOBJ);

#endif //OOP_CLASS_H
