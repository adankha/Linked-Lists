# Linked-Lists

Short C-Program dealing with the basics of Linked Lists

Class: CS 251 Data Structures, Spring 2015

Author: Ashour Dankha

This program requires llist.h, llist.c, and one of the mains labeled with an abbreviation of "test"

The program in this repository works with linked lists. Creating, pushing, popping, sorting, and going through the linked list are some of the  functions shown here. The program is only to help illustrate Linked Lists through the use of functions. The program also has run-time requirements for most of the functions.

Please read the comments, variable names, and function names to get a better sense of what is happening for each section of code.

Functions in llist.h:

// hidden implementation of list_struct
typedef struct list_struct LIST;

extern LIST *lst_create(); 

extern void lst_free(LIST *l);

extern void lst_print(LIST *l); 

extern void lst_push_front(LIST *l, ElemType val); 

extern void lst_push_back(LIST *l, ElemType val); 

extern int lst_len(LIST *l);

extern int lst_is_empty(LIST *l);

extern int lst_count(LIST *l, ElemType x); 

extern int lst_sanity1(LIST *l);

extern int lst_sanity2(LIST *l);

extern int lst_sanity3(LIST *l);

extern ElemType lst_pop_front(LIST *l); 

extern ElemType lst_pop_back(LIST *l);

extern void lst_print_rev(LIST *l); 

extern void lst_reverse(LIST *l); 

extern ElemType lst_remove_first(LIST *l, ElemType x) ;

extern ElemType lst_remove_all_slow(LIST *l, ElemType x) ;

extern LIST *lst_sra_bad_case(int n); 

extern int lst_remove_all_fast(LIST *l, ElemType x) ;

extern int lst_is_sorted(LIST *l);

extern void lst_insert_sorted(LIST *l, ElemType x);

extern void lst_merge_sorted(LIST *a, LIST *b);


