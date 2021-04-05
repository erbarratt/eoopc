#ifndef OOP_CLASS_H
#define OOP_CLASS_H
 
    //PUBLIC DEFINITION AND METHODS
 
	//typedef struct{
	//
	//	ePUB_PROP_DEC(int, prop1);
	//
	//	ePRIV_PROP_DEC(int, prop2, getset);
	//
	//	int (*method1)(void * eOBJ);
	//
	//} Class_t;
	
	struct Class_t{
		ePROP_DEC(int, prop1);
		
		ePRIV_PROP_DEC_PUB(int, prop2, get);
		
	};
		
	//Class_t Class_t_instantiate(int arg1, int arg2);
	void Class_t_instantiate(void * class);
	
	ePRIV_PROP_FUNC_DEC(Class_t, int, prop2, get)
	
	int Class_t_method1(void * eOBJ);

#endif //OOP_CLASS_H
