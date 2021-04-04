
#ifndef OOP_MAIN_H
	
	#include "p99/p99_if.h"
	
	#ifndef _STDIO_H
		#include <stdio.h>
	#endif //_STDIO_H
	
	#ifndef _STDLIB_H
		#include <stdlib.h>
	#endif //_STDLIB_H
	
	#define OOP_MAIN_H
	
	//define access types for encapsulation
		typedef enum { private, public } eACCESS;
	
	//messages
		#define eGETERR(o,x) fprintf(stderr, "Trying to access private property: " #o"."#x "()\n")
		#define eSETERR(o,x) fprintf(stderr, "Trying to write to private property: " #o"."#x "()\n")
		#define eMPROTERR(o,m,t) fprintf(stderr, "Trying to access private method: " #o"."#m "()\n")
		
	/*
	* Instantiate an object 'o' of type 'c' by using function 'c_instatiate()'
	* @param <classtype_t> c
	* @param var o Object variable name
	* @param ... any further arguments
	*/
		#define eNEW(c, ...) P99_IF_EMPTY(__VA_ARGS__) (c##_instantiate()) (c##_instantiate(__VA_ARGS__))
		
	/*
	* Cast "self" back into the class type
	* @param <classtype_t> c
	*/
		#define eSELF(c) c * self = (c*)eOBJ
	
	/*
	* Test access to given variable
	* @param var o Object
	* @param var p Object property
	*/
		#define ePROT(o,p) (o.p##_access == public)
	
	/*
	* Get the value of a protected variable 'x' within object 'o'
	* Prints to stderr if property is private
	* @param var o Object
	* @param var x Object property
	*/
		#define eGET(o, x, t) ePROT(o,x) ? o.x : (t)eGETERR(o,x)
	
	/*
	* Set the value of a protected variable 'x' within object 'o'
	* Prints to stderr if property is private
	* @param var o Object
	* @param var x Object property
	* @param var y The new value
	*/
		#define eSET(o, x, y) ePROT(o,x) ? (void)(o.x = y) : (void)eSETERR(o,x)
		
	/*
	* Call a protected method 'm' within object 'o'.
	* The first argument passed to method is always a pointer to the object 'o', to enable the use of eTHIS()
	* This means protected methods require first argument to always be 'void * obj'
	* Prints to stderr if method is private
	* @param var o Object variable name
	* @param function m The function to call
	* @param ... any further arguments to pass to method
	*/
		#define eMETH(o,m,t, ...) \
			ePROT(o,m)  \
				? P99_IF_EMPTY(__VA_ARGS__) ((t)(*o.m)(&o)) ((t)(*o.m)(&o, __VA_ARGS__))           \
				: (t)eMPROTERR(o,m,t)
	
	
	/*
	* Instantiate an object 'o*' of type 'c' by using function 'c_heap_instatiate()'
	* @param <classtype_t> c
	* @param var o Object variable name
	* @param ... any further arguments
	*/
		#define eNEW_H_INS(c,o, ...) P99_IF_EMPTY(__VA_ARGS__) (c##_heap_instantiate(o)) (c##_heap_instantiate(o, __VA_ARGS__))
	
	/*
	* Call allocation method and imediately fire instatiation function for heap object
	* @param <classtype_t> c
	* @param var o Object variable name
	* @param ... any further arguments
	*/
		#define eNEW_H(c,o, ...) (c *)malloc(sizeof(c)); eNEW_H_INS(c,o, __VA_ARGS__)
	
	/*
	* Free memory on heap for object
	* @param var o Object variable name
	*/
		#define eDESTROY_H(o) free(o)
	
	/*
	* Free memory on heap for object by calling definedd function to allow further actions
	* @param <classtype_t> c
	* @param var o Object variable name
	*/
		#define eDESTROY_H_M(c, o) c##_heap_destruct(o)
	
	/*
	* Test access to given member, in heap object
	* @param var o Object
	* @param var p Object property
	*/
		#define ePROT_H(o,p) (o->p##_access == public)
	
	/*
	* Get the value of a protected variable 'x' within object 'o', from heap object
	* Prints to stderr if property is private
	* @param var o Object
	* @param var x Object property
	*/
		#define eGET_H(o, x, t) ePROT_H(o,x) ? o->x : (t)eGETERR(o,x)
	
	/*
	* Set the value of a protected variable 'x' within object 'o', to heap object
	* Prints to stderr if property is private
	* @param var o Object
	* @param var x Object property
	* @param var y The new value
	*/
		#define eSET_H(o, x, y) ePROT_H(o,x) ? (void)(o->x = y) : (void)eSETERR(o,x)
		
	/*
	* Call a protected method 'm' within object 'o', from heap object
	* The first argument passed to method is always a pointer to the object 'o', to enable the use of eTHIS()
	* This means protected methods require first argument to always be 'void * obj'
	* Prints to stderr if method is private
	* @param var o Object variable name
	* @param function m The function to call
	* @param ... any further arguments to pass to method
	*/
		#define eMETH_H(o,m,t, ...) \
			ePROT_H(o,m)  \
				? P99_IF_EMPTY(__VA_ARGS__) ((t)(*o->m)(o)) ((t)(*o->m)(o, __VA_ARGS__))           \
				: (t)eMPROTERR(o,m,t)
		
#endif //OOP_MAIN_H
