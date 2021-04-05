
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
		#define eGETERR(o,x) fprintf(stderr, "Trying to access private property: " #o"."#x "() on line %d in file %s\n", __LINE__, __FILE__); exit(1);
		#define eSETERR(o,x) fprintf(stderr, "Trying to write to private property: " #o"."#x "() on line %d in file %s\n", __LINE__, __FILE__) exit(1);
		#define eMPROTERR(o,m) fprintf(stderr, "Trying to access private method: " #o"."#m "() on line %d in file %s\n", __LINE__, __FILE__)  exit(1);
		
	/*
	* Instantiate an object 'o*' of type 'c' by using function 'c_instatiate()'
	* @param <classtype_t> c
	* @param var o Object variable name
	* @param ... any further arguments
	*/
		#define eNEW_INS(c,o, ...) P99_IF_EMPTY(__VA_ARGS__) (c##_instantiate(o)) (c##_instantiate(o, __VA_ARGS__))
		
	/*
	* Instantiate an object 'o' of type 'c' by using function 'c_instatiate()'
	* @param <classtype_t> c
	* @param var o Object variable name
	* @param ... any further arguments
	*/
		#define eNEW(c,o, ...) struct c * o = NULL; eNEW_INS(c,o,__VA_ARGS__)
	
	/*
	* Call allocation method and imediately fire instatiation function for heap object
	* @param <classtype_t> c
	* @param var o Object variable name
	* @param ... any further arguments
	*/
		#define eNEW_H(c,o, ...) c*o = (c *)malloc(sizeof(c)); eNEW_H_INS(c,o, __VA_ARGS__)
	
	//public property declaration
		#define ePROP_DEC(t, p) t p
		#define ePROP_DEF(p, v) self->p = v
	
	//private property PUBLIC function-pointer declarations for public struct
		#define ePRIV_PROP_DEC_get(t,p) t (*get_##p)(void * eOBJ)
		#define ePRIV_PROP_DEC_set(t,p) void (*set_##p)(void * eOBJ, t v)
		#define ePRIV_PROP_DEC_getset(t,p) ePRIV_PROP_DEC_get(t,p); ePRIV_PROP_DEC_set(t,p)
		#define ePRIV_PROP_DEC_PUB(t, p, m) ePRIV_PROP_DEC_##m(t,p)
	
	//private property PRIVATE function-pointer declarations for private struct
		#define ePRIV_PROP_DEC_PRIV(t, p, m) ePROP_DEC(t,p); ePRIV_PROP_DEC_##m(t,p)
	
	//private property PUBLIC function delcarations
		#define ePRIV_PROP_FUNC_DEC_get(c, t, p) t c##_get_##p(void * eOBJ);
		#define ePRIV_PROP_FUNC_DEC_set(c, t, p) void c##_set_##p(void * eOBJ, t v );
		#define ePRIV_PROP_FUNC_DEC_getset(c, t, p) ePRIV_PROP_FUNC_DEC_get(c, t, p) ePRIV_PROP_FUNC_DEC_set(c, t, p)
		#define ePRIV_PROP_FUNC_DEC(c, t, p, m) ePRIV_PROP_FUNC_DEC_##m(c, t, p)
	
	//private property function allocations for object function pointers in instantiate
		#define ePRIV_PROP_DEF_get(c, p) self->get_##p = &c##_get_##p
		#define ePRIV_PROP_DEF_set(c, p) self->set_##p = &c##_set_##p
		#define ePRIV_PROP_DEF_getset(c, p) ePRIV_PROP_DEF_get(c, p); ePRIV_PROP_DEF_set(c, p)
		#define ePRIV_PROP_DEF(c, p, v, m) self->p = v; ePRIV_PROP_DEF_##m(c, p)
	
	
	
	#define ePRIV_PROP_FUNC_DEF_get(c, t, p) t c##_get_##p(void * eOBJ){ eSELF(c); return self->##p; }
	#define ePRIV_PROP_FUNC_DEF_set(c, t, p) void c##_set_##p(void * eOBJ, t v ){ eSELF(c); self->##p = v; }
	#define ePRIV_PROP_FUNC_DEF_getset(c, t, p) ePRIV_PROP_FUNC_DEF_get(c, t, p) ePRIV_PROP_FUNC_DEF_set(c, t, p)
	#define ePRIV_PROP_FUNC_DEF(c, t, p, m) ePRIV_PROP_FUNC_DEF_##m(c, t, p)
	
	
	
		
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
		#define ePROT(o,p) (o->p##_access == public)
	
	/*
	* Get the value of a protected variable 'p' within object 'o'
	* Prints to stderr if property is private
	* @param var o Object
	* @param var p Object property
	*/
		#define eGET(o, p) o->get_##p(o)
	
	/*
	* Set the value of a protected variable 'x' within object 'o'
	* Prints to stderr if property is private
	* @param var o Object
	* @param var p Object property
	* @param var v The new value
	*/
		#define eSET(o, p, v) o->set_##p(o, v)
		
		
	/*
	* Call a protected method 'm' within object 'o'.
	* The first argument passed to method is always a pointer to the object 'o', to enable the use of eTHIS()
	* This means protected methods require first argument to always be 'void * obj'
	* Prints to stderr if method is private
	* @param var o Object variable name
	* @param function m The function to call
	* @param ... any further arguments to pass to method
	*/
		#define eMETH(o,m, ...) \
			if ePROT(o,m) { \
				P99_IF_EMPTY(__VA_ARGS__) ((o->m)(o)) ((o->m)(o, __VA_ARGS__))     ;       \
			} else {                 \
				eMPROTERR(o,m);    \
			}
	
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
		
#endif //OOP_MAIN_H
