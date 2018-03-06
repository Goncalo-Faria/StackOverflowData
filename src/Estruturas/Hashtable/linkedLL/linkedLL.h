#ifndef LINKEDLL_h
#define LINKEDLL_h
/*  
    -> Linked List.

    This Module was created as part of a series of generic data structures implementations in C.
    
    If you decide to use the code please acknowledge the author.
        
    Author: Gonçalo Faria.
    Project: https://github.com/Goncalo-Faria/AbstractDatatyp_API.
*/

#include <stdlib.h>

typedef struct root* LL;
/*
    This is the data type that will represent the list.
*/


LL create_ll(void);
/*
    This function initiates the data structure.
    
    Complexity : 0(1). 

*/

int add_N(int (*ord )(void* , void*) ,LL x , void* op1, size_t fat );
    /*
        This method receives a function, a list and generic pointer block in memory and it's size.
        
        'add_N' will traverse the list and add a new node, either when it reachs the end or the function (f) returns -1 or 0.
        
        -> The function can also be used to edit the content of the linked list.
        
        Complexity : O(n)
        
    */
int rem_N( int (*f )(void* , void*) ,LL x ,void* op1 );
    /*        
        This method receives a function, a list and a generic pointer block in memory.
        
        'rem_N' will remove every element that triggers (makes f return 1) the input function.
        
        The function can also be used to edit the content of the linked list.

        Complexity : O(n)
        
    */

void* ind_ll( LL x , int i, size_t * s );
    /*
        i is the index. And the value that 's' is pointing to will have the size of the returned memory block.

        Complexity : O(n)
    */

  

int empty_ll( LL x );
    /*  
        0(1)
        This function checks if the list is empty.
    */

void clean_ll( LL x );
    /*
        This function free's every single piece of memory that the list is using. 
        
        Complexity : 0(n)
    */

void print_ll(LL x, void (*show)(void *));
    /*
        This function print's the content of the list acording to a input function.
        
        Complexity : 0(n)
    */

void fmap_ll( void (*f) (void*, void*) , LL x, void* op1 );
    /*
        0(n)
        This function affects a tranformation to everysingle element of the list.

        the flag will be the first operant of the function.

    */

int length_ll( LL x );
    /*
        Returns the length of the linked list.
        Complexity : 0(1)
    */

void* search_ll( int (*eq) (void*, void*), LL x, void* op1 );
    /*
        Whenever the function 'eq' returns 1 while having as arguments op1 and the data stored in the linked list
        the pointer to the data in the node shall be returned.
        
        The arguments of eq will be assigned in the order mentioned above.
        eq( op1, DATA )
        Complexity : O(n)
    */

#endif