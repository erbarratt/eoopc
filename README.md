# eOOPc
Small macro based OOP implementation for C

Why OOP in base C?
-

Because you can. Because some projects make more sense written using OOP concepts. Because pointers are awesome.

Writing code in the eOOPc style
-
This article assumes prior knowledge of OOP concepts such as encapsulation, inheritance, polymorphism, properties and methods. These will not be covered here.

Firstly, let's define some structural practices to follow that make the code readable and understandable.

In eOOPC style, classes are split into 3 files:

- Public declaration
- Private declaration
- Private definition / source

Using the filename prefixes of:

- _pub.h
- _class.h
- _class.c

eOOPc style doesn't define where files should be stored.

To start our Person/Student example, we could therefor define our files as such:

- person_pub.h
- person_class.h
- person_class.c

Public declaration files
-

The _pub.h file is the header file that will be included in the source files you intend to instantiate any objects.
The purpose of the public declaration file is to expose only the class struct members you'll define as publically accessible.

Public declaration files should contain only:

- The public struct declaration
- The class instatiation function declaration
- Any other declarations needed to declare the structure (other structs, enums etc)

In eOOPc style, we layout this code as follows:

```
    [other structure declarations]
    
    struct &lt;classname&gt;_t {
        [public properties]
        [public method pointers]  
    };
    
    [Optional private/public typecast]
    
    classname_t_instantiate(void * eOBJ);
```

For example, our person_pub.h file could be:

```
#ifndef PERSON_PUBLIC_H
#define PERSON_PUBLIC_H

    /**
    * Person class PUBLIC structure
    */
        struct Person_t {
            
            //public properties
                int height;
                int age;
                char firstname[50];
                char surname[50];
                
            //public methods
                void (*printName)(void * eOBJ);
                
        };
        
    Person_t_instantiate(void * eOBJ);

#endif
```

As you can see, our person class has four public properties, and one public method.

The method is actually declared as a function pointer. Note the subtle difference between `(void*) printName(void * eOBJ)` and `void (*printName)(void * eOBJ)`. 
Here we're declaring that the member `printName` is a function pointer, whose return type is `void` and who will accept arguments `void * eOBJ`. 
In C, we store a pointer, pointing to a function we'll declare and define in the private class files.

The `[optional private/public typecast]` is used when a _class.h header file is not needed. When? When the class will have no private members. If this were true for our Person class,
we'd add `typecast struct Person_t Person_t;` here. Seeing as our Person class will contain private members, this typecast will be done in the _class.h file instead (see below). 

void * eOBJ
-

In eOOPc, the argument `void * eOBJ` is used at the first argument of any class method that requires access to that objects properties and methods.

In other languages, `this` is done behind the scenes, but uses essentially the same logic. 

Note it is required by any `&lt;classname&gt;_t_instatiate()` function for some eOOPC macros to work, and is present in the sole public `printName` method in the Person class.

Private declaration files
-

The _class.h header file is used by the _class.c file of this class, or any class that wishes to inherit / use the private members of a class.

Here we can declare a number of things:

- A Virtual Method Table (vmt) for private methods
- The private typecast of the classname_t structure to a type (also defining private members and method class pointers)
- Declarations for the private methods that will get pointed to

In eOOPc style, we layout this code as follows:

```

    #include "classname_pub.h"
    
    [optional vmt struct declaration]
    
    [optional vmt method declarations...]
    
    typedef struct {
        [public properties]
        [public method pointers]
        [private properties]
        [private vmt pointer]
    } classname_t;

    [optional method function declarations]

```

By having the `[optional method function declarations]` in this file, it stops any calling function from being able to call them directly. Instead
an object of type classname_t must be instantiated, then the corresponding method pointer called.

Our Person's private declaration file could be:

```
#ifndef PERSON_PUBLIC_H
#define PERSON_PUBLIC_H

#include "Person_pub.h"

    /**
    * Person class PRIVATE vmt structure
    */
        struct Person_t_vmt {
            void (*getWeight)(void * eOBJ);
        };
    
    //function declarations for private methods via vmt
        Person_t_vmt_instantiate(void * eOBJ);
        Person_t_getWeight(void * eOBJ);

    /**
    * Person class PRIVATE structure
    */
        typedef struct {
            
            //public properties
                int height;
                int age;
                char firstname[50];
                char surname[50];
                
            //public methods
                void (*printName)(void * eOBJ);
                
            //private properties
                int weight;
                
            //private methods via virtual method table struct
                struct Peron_t_vmt* vmt;
                
        } Person_t;
        
    //function declarations for public methods
        Person_t_printName(void * eOBJ);

#endif
```

First, we include `Person_pub.h` to be able to make a typedef using the public struct.

Then we define a struct `Person_t_vmt` that will act as a member that holds the methods in our Person class we want to keep private. This sub class needs it's own `_instantiate()` function.

Seeing as the whole declaration for the vmt is within this private _class.h file, only source files that include this header will have access to it (thereby, implicitly having access to the main private class declaration anyway).

We've added `int weight` as a private property, and a pointer of type `Person_t_vmt` to act as our holder for private methods.

Whilst primitive types (and all pointers) can be added as private members to a struct typedef, <b>function pointers can not.</b> Trying to add a function pointer as a private member will result in a stack smash, which is why we need the vmt.

