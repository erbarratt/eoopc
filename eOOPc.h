#ifndef OOP_MAIN_H
#define OOP_MAIN_H
	
	#ifndef _STDLIB_H
		#include <stdlib.h>
	#endif
	
	#ifndef P99_IF_H_
		#include "p99/p99_if.h"
	#endif

	/**
	* grab an interface definition by calling it's macro.
	* @param i Interface name
	*/
		#define eIMPLEMENTS(i) eINTERFACE_##i()

	/**
	* add a parent class struct to gain access to it's public methods
	* @param p Struct name
	* @param n Property name
	*/
		#define eEXTENDS(p,n) struct p n

	/**
	* helper macro to denote that this parent is upcastable (this macro must be first element of containing
	* struct for this to be true)
	* @param p Struct name
	* @param n Property name
	*/
		#define eDIR_EXTENDS(p,n) eEXTENDS(p, n)
	
	/**
	* Instantiate an object 'o*' of type 'c' by using function 'c_instatiate()'
	* @param <classtype_t> c
	* @param var o Object variable name
	* @param ... any further arguments
	*/
		#define eNEW_INS(c,o, ...) P99_IF_EMPTY(__VA_ARGS__) (c##_instantiate(o)) (c##_instantiate(o, __VA_ARGS__))
	
	/**
	* Call allocation method and imediately fire instatiation function for heap object
	* @param <classtype_t> c
	* @param var o Object variable name
	* @param ... any further arguments
	*/
		#define eNEW(c,o, ...) struct c*o = (struct c *)malloc(sizeof(struct c)); eNEW_INS(c,o, __VA_ARGS__)
	
	/**
	* public property DECLARATION
	* @param t Type
	* @param p Property name
	*/
		#define ePROP_DEC(t, p) t p
	
	/**
	* public property DEFINITION
	* @param p Property name
	* @param v Value
	*/
		#define ePROP_DEF(p, v) self->p = v
	
	/**
	* private property PUBLIC function-pointer DECLARATIONS for public struct
	* @param t Type
	* @param p Property name
	* @param m get/set/getset
	*/
		#define ePRIV_PROP_DEC_get(t,p) t (*get_##p)(void * eOBJ)
		#define ePRIV_PROP_DEC_set(t,p) void (*set_##p)(void * eOBJ, t v)
		#define ePRIV_PROP_DEC_getset(t,p) ePRIV_PROP_DEC_get(t,p); ePRIV_PROP_DEC_set(t,p)
		#define ePRIV_PROP_DEC_PUB(t, p, m) ePRIV_PROP_DEC_##m(t,p)
	
	/**
	* private property PRIVATE function-pointer DECLARATIONS for private struct
	* @param t Type
	* @param p Property name
	* @param m get/set/getset
	*/
		#define ePRIV_PROP_DEC_PRIV(t, p, m) ePROP_DEC(t,p); ePRIV_PROP_DEC_##m(t,p)
	
	/**
	* private property PUBLIC function DECLARATIONS
	* @param c Type
	* @param t Function return type
	* @param p Property name
	* @param m get/set/getset
	*/
		#define ePRIV_PROP_FUNC_DEC_get(c, t, p) t c##_get_##p(void * eOBJ);
		#define ePRIV_PROP_FUNC_DEC_set(c, t, p) void c##_set_##p(void * eOBJ, t v );
		#define ePRIV_PROP_FUNC_DEC_getset(c, t, p) ePRIV_PROP_FUNC_DEC_get(c, t, p) ePRIV_PROP_FUNC_DEC_set(c, t, p)
		#define ePRIV_PROP_FUNC_DEC(c, t, p, m) ePRIV_PROP_FUNC_DEC_##m(c, t, p)
	
	/**
	* private property function ALLOCATIONS for object function pointers in instantiate
	* @param c Type
	* @param p Property name
	* @param v Property value
	* @param m get/set/getset
	*/
		#define ePRIV_PROP_DEF_get(c, p) self->get_##p = &c##_get_##p
		#define ePRIV_PROP_DEF_set(c, p) self->set_##p = &c##_set_##p
		#define ePRIV_PROP_DEF_getset(c, p) ePRIV_PROP_DEF_get(c, p); ePRIV_PROP_DEF_set(c, p)
		#define ePRIV_PROP_DEF(c, p, v, m) self->p = v; ePRIV_PROP_DEF_##m(c, p)
	
	/**
	* private property PUBLIC get/set function DEFINITIONS
	* @param c Type
	* @param t Function return type
	* @param p Property name
	* @param m get/set/getset
	*/
		#define ePRIV_PROP_FUNC_DEF_get(c, t, p) t c##_get_##p(void * eOBJ){ eSELF(c); return self->p; }
		#define ePRIV_PROP_FUNC_DEF_set(c, t, p) void c##_set_##p(void * eOBJ, t v ){ eSELF(c); self->p = v; }
		#define ePRIV_PROP_FUNC_DEF_getset(c, t, p) ePRIV_PROP_FUNC_DEF_get(c, t, p) ePRIV_PROP_FUNC_DEF_set(c, t, p)
		#define ePRIV_PROP_FUNC_DEF(c, t, p, m) ePRIV_PROP_FUNC_DEF_##m(c, t, p)
	
	/**
	* Cast "self" back into the class type
	* @param <classtype_t> c
	*/
		#define eSELF(c) c * self = (c*)eOBJ
	
	/**
	* Get the value of a protected variable 'p' within object 'o'
	* Prints to stderr if property is private
	* @param var o Object
	* @param var p Object property
	*/
		#define eGET(o, p) o->get_##p(o)
	
	/**
	* Set the value of a protected variable 'x' within object 'o'
	* Prints to stderr if property is private
	* @param var o Object
	* @param var p Object property
	* @param var v The new value
	*/
		#define eSET(o, p, v) o->set_##p(o, v)
	
	/**
	* Method call wrapper that passes object as first argument for use of eSELF()
	* @param var o Object
	* @param var m The method
	* @param ... Other args
	*/
		#define eMETH(o, m, ...) P99_IF_EMPTY(__VA_ARGS__) ((*o->m)(o)) ((*o->m)(o, __VA_ARGS__))
		
	/**
	* Free memory on heap for object
	* @param var o Object variable name
	*/
		#define eDESTROY(o) free(o); o = ((void*)0)
	
	/**
	* Free memory on heap for object by calling defined function to allow further actions
	* such as destroying string / struct members within object
	* @param <classtype_t> c
	* @param var o Object variable name
	*/
		#define eDESTROY_M(c, o) c##_heap_destruct(o); o = ((void*)0)
		
#endif //OOP_MAIN_H
