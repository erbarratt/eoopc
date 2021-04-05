#ifndef OOP_CLASS_H
#define OOP_CLASS_H
 
//PUBLIC DEFINITION AND METHODS
	
	struct Class_t{
		//define a public property
			ePROP_DEC(int, prop1);
			
		//define function pointers for get, set or both for private property
			ePRIV_PROP_DEC_PUB(int, prop2, get);
		
		//public method function pointer
			int (*method1)(void);
		
	};
	
//public class function declarations

	//get and/or set PUBLIC function declarations
		ePRIV_PROP_FUNC_DEC(Class_t, int, prop2, get)
	
	//other defined public methods
		int Class_t_method1(void);

	//always need an instantiate. Void pointer so function can cast back to struct type pointer
	//this means we don't get conflicting type errors
		void Class_t_instantiate(void * eOBJ);

#endif //OOP_CLASS_H
