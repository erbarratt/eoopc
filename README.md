# eOOPc
Small macro based OOP implementation for C

### Why OOP in base C?

Because you can. Because some projects make more sense written using OOP concepts. Because pointers are awesome.

### Writing code in the eOOPc style
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

### Public declaration files

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
                void (*printStats)(void * eOBJ);
                
        };
        
    void Person_t_instantiate(void * eOBJ, int height, int age, int weight, char * firstname, char * surname);

#endif
```

As you can see, our person class has four public properties, and one public method.

The method is actually declared as a function pointer. Note the subtle difference between `(void*) printName(void * eOBJ)` and `void (*printName)(void * eOBJ)`. 
Here we're declaring that the members `printName` and `printStats`are function pointers, whose return type is `void` and who will accept arguments `void * eOBJ`. 
In C, we store a pointer, pointing to a function we'll declare and define in the private class files.

The `[optional private/public typecast]` is used when a _class.h header file is not needed. When? When the class will have no private members. If this were true for our Person class,
we'd add `typecast struct Person_t Person_t;` here. Seeing as our Person class will contain private members, this typecast will be done in the _class.h file instead (see below).

#### void * eOBJ

In eOOPc, the argument `void * eOBJ` is used at the first argument of any class method that requires access to that objects properties and methods.

In other languages, `this` is done behind the scenes, but uses essentially the same logic. 

Note it is required by any `&lt;classname&gt;_t_instatiate()` function for some eOOPC macros to work, and is present in the sole public `printName` method in the Person class.

### Private declaration files

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
            int (*getWeight)(void * eOBJ);
        };
    
    //function declarations for private methods via vmt
        void Person_t_vmt_instantiate(void * eOBJ);
        int Person_t_getWeight(void * eOBJ);

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
        void Person_t_printName(void * eOBJ);
        void Person_t_printStats(void * eOBJ);

#endif
```

First, we include `Person_pub.h` to be able to make a typedef using the public struct.

Then we define a struct `Person_t_vmt` that will act as a member that holds the methods in our Person class we want to keep private. This sub class needs it's own `_instantiate()` function.

Seeing as the whole declaration for the vmt is within this private _class.h file, only source files that include this header will have access to it (thereby, implicitly having access to the main private class declaration anyway).

We've added `int weight` as a private property, and a pointer of type `Person_t_vmt` to act as our holder for private methods.

Whilst primitive types (and all pointers) can be added as private members to a struct typedef, <b>function pointers can not.</b> Trying to add a function pointer as a private member will result in a stack smash, which is why we need the vmt.

Note that the private declaration also needs all the members of the public declaration in the same order, followed by any private members.

### Private definition / source file

The private definition file contains the actual logic and source code for all the declared items in both the _pub.h and _class.h files.

It requires access to both to prevent having to redeclare any members or functions.

In eOOPc style, we layout this code as follows:

```
    [optional included headers]
    #include "classname_pub.h"
    #include "classname_class.h"
    
    [optional classname_vmt_instantiate() function]
    
    [optional vmt private methods]
    
    classname_instatiate(void * eOBJ){
        
        [public properties]
        
        [public methods]
        
        [privvate properties]
        
        [private vmt methods]
        
    }
    
    [optional public methods]
    
```

So our person source file becomes:

```
    #include <stdio.h>
    #include <string.h>
    #include "person_pub.h"
    #include "person_class.h"
    
    //VMT
        /**
        * Instantiate a Person class vmt
        * @param void* eOBJ Self (Class vmt)
        * @return void
        */
            void Person_t_vmt_instantiate(void * eOBJ)
            {
                //cast eOBJ back into class vmt type pointer
                    eSELF(Person_t_vmt);
            
                //define private methods 
                    self->getWeight = &Person_t_getWeight;
                    
            }
        
        /**
        * Get a person weight
        * @param void* eOBJ Self (class)
        * @return int
        */
            int Person_t_getWeight(void * eOBJ)
            {
                //cast eOBJ back into class (NOT vmt!) type pointer
                    eSELF(Person_t);
            
                //define private methods 
                    return self->weight;
                    
            }
            
    //Main CLASS
    
         /**
        * Instatiate a Person Object
        * @param void* eOBJ Self (class)
        * @param int height
        * @param int age
        * @param int weight
        * @param char* firstname
        * @param char* surname
        * @return void
        */
            void Person_t_instantiate(void * eOBJ, int height, int age, int weight, char * firstname, char * surname)
            {
                //cast eOBJ back into class type pointer
                    eSELF(Person_t);
                    
                    //public members
                        self->height = height;
                        self->age = age;
                    
                    //allocate memory for the string pointers (50 chars max)
                    //we want a copy of the information, not the original pointer
                        self->firstname = (char*) malloc(51 * sizeof(char));
                        strcpy(self->firstname, firstname);
                        self->surname = (char*) malloc(51 * sizeof(char));
                        strcpy(self->surname, surname);
                        
                    //public methods
                        self->printName = &Person_t_printName;
                        self->printStats = &Person_t_printStats;
                        
                    //private members
                        self->weight = weight;
                        
                    //private methods vmt instantiation
                        self->vmt = eNEW(Person_t_vmt);
                        eCONSTRUCT(Person_t_vmt, self->vmt);
                    
            }
        
         /**
        * Print a Person's full name
        * @param void* eOBJ Self (class)
        * @return void
        */
            void Person_t_printName(void * eOBJ)
            {
                 //cast eOBJ back into class type pointer
                    eSELF(Person_t);
                    
                char tmp[101];
                strcpy(tmp, self->firstname);
                strcat(tmp, " ");
                strcat(tmp, self->surname);
                printf("%s\n", tmp);
                
            }
            
         /**
        * Print the Stat's of a person
        * @param void* eOBJ Self (class)
        * @return void
        */
            void Person_t_printStats(void * eOBJ)
            {
                 //cast eOBJ back into class type pointer
                    eSELF(Person_t);
                 
                 printf(
                    "Height: %dcm, Age: %d years, Weight: %dlbs\n", 
                    self->height,
                    self->age,
                    self->vmt->getWeight(self)
                );
            
            }

```

First we include some standard library headers for the below functions, as well as the _pub.h and _class.h files.

This gives us access to the full blueprint declarations for our class, which is mostly useful for being able to write the source file in the order that the _class.h file is in.

#### Person_t_vmt_instantiate()

The first function to define is the instantiation function for the private VMT object. 
Note the `_vmt` in the function name.
Here we see the `eSELF()` macro, which is always used in combination with the `void * eOBJ` pointer, defined as:

    #define eSELF(c) c * self = (c*)eOBJ

Passing this macro a struct type casts the `eOBJ` pointer back into a pointer of that type. In this case, the replacement will be `Person_t_vmt * self = (Person_t_vmt*)eOBJ`. This allows us to easily use `self->` in our function to mean the VMT object.

The instantiation function also contains the definition of the function pointer `int (*getWeight)(void * eOBJ)` to point at . This is the only private method in the Person class.

#### Person_t_getWeight()

This is followed by the definition of the `Person_t_getWeight()` function. Note, it could just as easily have been named `Person_t_vmt_getWeight` which more explicitly marks it as a VMT function however, 
it's generally best to reserve the `_vmt` for methods private to the VMT object itself. By ommitting the `_vmt` we are implicitly saying this function belongs to the Person_t class itself as a private method, via the vmt.

Note, in this function we're not passing the type of `Person_t_vmt` to the `eSELF()` macro, but the main `Person_t` type. The struct `Person_t_vmt` doesn't contain any property `weight`, so we need to pass the main `Person_t` object to this function instead.
This is standard practice for using a vmt within a main class. You will more than often pass the main class object rather than the vmt sub object to any vmt method.

#### Person_t_instantiate()

The `Person_t_intantiate` function is the only `Person_t_` function that has been publically declared, for the obvious reason that any source wishing to instantiate an object of type `Person_t` needs access to it. Hence it's original declaration was in the _pub.h file, not the _class.h file.

The first argument is, as ever, `void * eOBJ` to use the `eSELF()` macro with. After casting back to the `Person_t` type, we can then assign all the public and private properties using the other arguments passed.

Note, for the string pointer properties `firstname` and `surname`, we want a COPY of the passed text to reside within the class. This means we need to allocate memory for them, and copy the passed strings into that new memory. This prevents those strings being destroyed at the end
of whatever scope called this instantiation function.

Doing a simple `self->firstname = firstname` would risk having that pointer point to garbage at some point in the future. By allocating memory,we ensure the survival of the string information for the lifetimeof the object.

The final operation is to create and instantiate the vmt sub object. We do this with another eOOPc macro `eNEW()`, defined as:

    #define eNEW(c) (struct c *)malloc(sizeof(struct c))

This macro - whilst simple again - is to mimic other languages use of `class object = new class()` syntax.
In this case, the macro expands to:

    (struct Person_t_vmt *)malloc(sizeof(struct Person_t_vmt));
    
Here we allocate memory for the subobject and cast the `malloc()` call back to the type of `Person_t_vmt*`.

After allocation of memory, we then need to instantiate the object by using the macro `eCONSTRUCT()` which is a variadic macro defined as:

    #define eCONSTRUCT(c, ...) c##_instantiate(__VA_ARGS__)
    
In our case, this expands to the function call:

    Person_t_vmt_instantiate(self->vmt);
    
As you can see, we have passed the pointer `self->vmt` of type `Person_t_vmt` to use as the `void * eOBJ` argument in the `Person_t_vmt_instantiate()` function.

Note also, that because the declaration AND definition of the function `Person_t_vmt_instantiate` exists only in the _class.h and this private class source file, it's not accessible anywehere else.

#### Person_t_printName()

Here we define a simple function to concatenate and print to console the combined `firstname` and `surname` properties. As a side note, see that the definition `char tmp[101]` is a combination of
50 + 50 + 1. We only need one '\0' terminating character, so it doesn't need to be length 102.

Again, we're passing the object to `void * eOBJ` and casting back into a pointer of type `Person_t` using the `eSELF()` macro.

#### Person_t_printStats()

This function shows how we can use private methods on the vmt table, where we make a call to `self->vmt->getWeight(self)`. Note again,
we pass the `self` object to this function, not the `self->vmt` object. 

### Using our new class

We've already seen the usage of the `eNEW` and `eCONSTRUCT` eOOPc macros. Making an object of type `Person_t` is no different:

```

    //include the public definition
        #include "person_pub.h"
        
    int main(){
    
        struct Person_t* person = eNEW(Person_t);
        eCONSTRUCT(Person_t, person);
        
        eCALLna(person, printName);
        //same as person->printName(person);
        
        printf("Our person is %d years old\n", person->age);
        
        eCALLna(person, printStats);
        //same as person->printStats(person);
        
        /**
        * None of the following will work as they're all private:
        * 
        * printf("Our person is %d lbs\n", person->weight);
        * 
        * int weightLocal = person->vmt->getWeight(person);
        *
        * Person_t_printName(person);
        * 
        */
    
        return 0;
    
    }

```

By structuring the class in the _pub.h, _class.h and _class.c files, we've ensured that by only including the _pub.h file, the `main()` function does not have access to:

- Person_t_printName() directly
- Person_t_printStats() directly
- Person_t_getWeight() directly
- person->weight

This is because both the declarations and definitions for the above are in the _class.h and _class.c files, neither of which are referenced here.

Another eOOPc macro is also introduced above, the `eCALLna` macro, defined as:

    #define eCALLna(o,m) (*o->m)(o)
    
This is another helper macro to make calling methods with no arguments easier to write. It gets expanded in this case to:

    (*person->printName)(person)
    
