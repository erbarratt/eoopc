#ifndef OOP_MAIN_H
#define OOP_MAIN_H
	
	#ifndef _STDLIB_H
		#include <stdlib.h>
	#endif
	
	#ifndef P99_IF_H_
		#include "p99/p99_if.h"
	#endif

	//interface definitions can contain expressly written variables,
	//other e@ macros etc as needed.
		#define eINTERFACE_interface() \
			int poop; \
			int shmoop

	//grab an interface definition by calling it's macro.
		#define eIMPLEMENTS(i) eINTERFACE_##i()

	//add a parent class struct to gain access to it's public methods
		#define eEXTENDS(p) struct p

	//helper macro to denote that this parent is upcastable (this macro must be first element of containing
	//struct for this to be true
		#define eDIR_EXTENDS(p) eEXTENDS(p)
	
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
		//#define eNEW(c,o, ...) struct c o##_v; struct c * o = &o##_v; eNEW_INS(c,o,__VA_ARGS__)
	
	/*
	* Call allocation method and imediately fire instatiation function for heap object
	* @param <classtype_t> c
	* @param var o Object variable name
	* @param ... any further arguments
	*/
		#define eNEW(c,o, ...) struct c*o = (struct c *)malloc(sizeof(struct c)); eNEW_INS(c,o, __VA_ARGS__)
	
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
	
	
	//private property PUBLIC get/set function definitions
		#define ePRIV_PROP_FUNC_DEF_get(c, t, p) t c##_get_##p(void * eOBJ){ eSELF(c); return self->p; }
		#define ePRIV_PROP_FUNC_DEF_set(c, t, p) void c##_set_##p(void * eOBJ, t v ){ eSELF(c); self->p = v; }
		#define ePRIV_PROP_FUNC_DEF_getset(c, t, p) ePRIV_PROP_FUNC_DEF_get(c, t, p) ePRIV_PROP_FUNC_DEF_set(c, t, p)
		#define ePRIV_PROP_FUNC_DEF(c, t, p, m) ePRIV_PROP_FUNC_DEF_##m(c, t, p)
	
	/*
	* Cast "self" back into the class type
	* @param <classtype_t> c
	*/
		#define eSELF(c) c * self = (c*)eOBJ
	
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
