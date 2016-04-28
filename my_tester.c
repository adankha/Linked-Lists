
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// very incomplete small test program...

int main() {
/*    
    LIST *lst1;
    LIST *lst2;
    int i;

    lst1 = lst_create();
    
    for(i=0; i<7; i++) {
        lst_push_front(lst1, i);
    }
    
    lst2 = lst_create();
    
    
    for(i=0; i<5; i++) {
        lst_push_back(lst2, 5);
    }

    for (i = 0; i < 9; i++)
	lst_push_back(lst2, 30);

    for(i=0; i<5; i++) {
        lst_push_back(lst2, 100);
        
        
    }
    
    for (i = 0; i < 5; i++)
	lst_push_front(lst2, 22); 
   


    for (i = 0; i < 5; i++)
	lst_push_front(lst2, 8); 

    for (i = 0; i < 5; i++)
        lst_push_front(lst2, 3); 


 
    //lst_push_front(lst2, 3);
    printf("lst_len(lst1) : %i\n", lst_length(lst1));
    printf("lst1 contents: ");
    lst_print(lst1);
    
printf("Testing sanity 2..... %d\n", lst_sanity2(lst1));
    printf("The reverse order is!!!\n\n");
    lst_print_rev(lst1);
    printf("\n");    
    
printf("Testing sanity 2..... %d\n", lst_sanity2(lst1));
    lst_pop_front(lst1);
    lst_pop_front(lst1);
    printf("lst1 contents after two pops: ");
    lst_print(lst1);
    
printf("Testing sanity 2..... %d\n", lst_sanity2(lst1));
printf("HELLO I AM TESTING THE POP FUNCTION: LOOK HERE %d\n\n\n",   lst_pop_back(lst1));
    printf("Popping the back now!");
    lst_print(lst1);   
    
printf("Testing sanity 2..... %d\n", lst_sanity2(lst1));
    
    printf("number of 3's = %i\n", lst_count(lst1, 3));
    printf("number of 0's = %i\n", lst_count(lst1, 0));
    lst_print(lst1);

printf("Testing sanity 2..... %d\n", lst_sanity2(lst1));

    //printf("list 2 before removing\n");
    //lst_print(lst2);
    printf("Now we are going to insert in the sorted list!!\n");
    lst_insert_sorted(lst1, 2);
    lst_is_sorted(lst1);
    
printf("Testing sanity 2..... %d\n", lst_sanity2(lst1));
    printf("Removing:\n");
    //   lst_remove_all_slow(lst2, 5);
    lst_remove_all_fast(lst2, 5);
    lst_print(lst1);
    
printf("Testing sanity 2..... %d\n", lst_sanity2(lst1));
    printf("First list is:\n");
    lst_reverse(lst1);
    lst_print(lst1);
    
//printf("Testing sanity 2..... %d\n", lst_sanity2(lst1));
    printf("Second list is:\n");
    //lst_reverse(lst2); 
lst_push_back(lst2, 103);  
    
printf("HELLLLLLOOOOOOOOOOOOOOOOOOOO\n");
lst_print(lst1);
lst_print(lst2);
printf("Size of list 1: %d size of list 2: %d \n", lst_length(lst1), lst_length(lst2));    
    lst_merge_sorted(lst1, lst2);
    printf("Results after merge\n");
    lst_print(lst1);
//    lst_is_sorted(lst1);
    lst_print(lst2);

//printf("Testing sanity 2..... %d\n", lst_sanity2(lst1));

   ** test code for lst_push_back **
	printf("\n\nOkay... time to test the new functions!!!!\n\n");
	printf("lst_to_array stuff!\n");    
    int arrayTest[200];
	int count = 0;
    for (i = 0; i < 15;i++){
    arrayTest[i] = count;
    count++;
} 
printf("WE are testing the length of the linked list!!!!\n");
lst_print(lst1);
lst_print(lst2);
printf("\n\n\n\n %d", lst_length(lst1));
   lst_print( lst_from_array(arrayTest, 15));


	printf("lst from array stuff\n");
	ElemType *testingshit;
	lst_print(lst1);	
        testingshit = lst_to_array(lst1);
        for (i = 0; i < lst_length(lst1); i++)
	printf("%d ",testingshit[i]);



printf("\nTIME TO TEST THE LIST PREFIX STUFF!!!\n\n");

printf("Lets first print out the linked list we are working with.");

lst_print(lst1);


//printf("Testing sanity 2..... %d\n", lst_sanity2(lst1));
lst_print(lst_prefix(lst1, 10));
printf("\n");
lst_print(lst1);

//printf("Testing sanity 2..... %d\n", lst_sanity2(lst1));
printf("TIME TO TEST list_filter_leq\n");

lst_print(lst_filter_leq(lst1, 1));

//printf("Testing sanity 2! %d\n", lst_sanity2(lst1));
printf("We are printing the first list\n");
lst_print(lst1);
lst_print(lst2);
//lst_free(lst2);
//lst2 = create();


    for (i = 0; i < 5; i++)
	lst_push_front(lst2, 22); 
   


    for (i = 0; i < 5; i++)
	lst_push_front(lst2, 8); 

    for (i = 0; i < 5; i++)
        lst_push_front(lst2, 3); 

lst_print(lst2);


lst_concat(lst1, lst1);

printf("concat!!!\n");

lst_print(lst1);
    lst_free(lst1);
*/
LIST *test = lst_create();

        lst_push_front(test, 2); 
        lst_push_front(test, 4); 
        lst_push_front(test, 9); 
        lst_push_front(test, 5); 
        lst_push_front(test, 5); 
        lst_push_front(test, 2); 
        lst_push_front(test, 4); 
        lst_push_front(test, 5); 
        lst_push_front(test, 5); 
        lst_push_front(test, 9); 

lst_print(test);

remove_all_x(test, 5);

lst_print(test);






}
  
