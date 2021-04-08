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
    
    struct <classname>_t {
        [public properties]
        [public methods]  
    };
    
    <classname>_t_instantiate(void * eOBJ);
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

void * eOBJ
-

In eOOPc, the argument void * eOBJ is used at the first argument of any class method that requires access to that objects properties and methods.

In other languages, `this` is done behind the scenes, but uses essentially the same logic. 

Note it is required by any `<classname>_t_instatiate()` function, and is present in the sole public method in the Person class.

