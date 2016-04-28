#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct node {
    ElemType val;
    struct node *next;
} NODE;


struct list_struct {
    NODE *front;
    NODE *back;
    int count_size;
};


/*
* returns pointer to newly created empty list
*/
LIST *lst_create() {
    LIST *l = malloc(sizeof(LIST));
    
    l->front = NULL;
    l->back = NULL;
    l->count_size = 0;
    return l;
}

void lst_free(LIST *l) {
    NODE *p = l->front;
    NODE *pnext;
    
    while(p != NULL) {
        pnext = p->next;   // keeps us from de-referencing a freed ptr
        free(p);
        p = pnext;
    }
    // now free the LIST
    free(l);
}

void lst_print(LIST *l) {
    NODE *p = l->front;
    
    printf("[");
    while(p != NULL) {
        printf(FORMAT, p->val);
        p = p->next;
    }
    printf("]\n");
}

/**
* TODO:  print in reverse order
*
* Try to do without looking at notes!
* Hints:  recursive helper function
*/
void print_reverse_helper( NODE *help){
    
    
    if (help == NULL)	// Base case. When it reaches NULL, go back and print
        return;
    
    print_reverse_helper(help->next);
    printf(FORMAT, help->val); // We want the helper function to go to the end then print
    
}

void lst_print_rev(LIST *l) {
    
    NODE* current = l->front;   // Initialize a pointer to point to the start of the list
    printf("[");    
    if (current == NULL)
    {
	printf("]\n");	
        return;
    }
    if (current->next == NULL)
    {
        printf(FORMAT, current->val);
	printf("]\n");
        return;
    }
    
    print_reverse_helper(current);
    printf("]\n");
    
}

void lst_push_front(LIST *l, ElemType val) {
    NODE *p = malloc(sizeof(NODE));
    
    p->val = val;
    p->next = l->front;
    l->count_size++;
    l->front = p;
    if(l->back == NULL)   // was empty, now one elem
        l->back = p;
}

void lst_push_back(LIST *l, ElemType val) {
    NODE *p;
    
    if(l->back == NULL)   // list empty - same as push_front
        lst_push_front(l, val);
    else {  // at least one element before push
        p = malloc(sizeof(NODE));
        p->val = val;
        p->next = NULL;
        l->back->next = p;
        l->count_size++;
        l->back = p;
    }
}

int lst_length(LIST *l) {
    
    return l->count_size;
}

int lst_is_empty(LIST *l) {
    return l->front == NULL;
}


/** TODO
 *    function:  lst_count
*     description:  Counts number of occurrences
*     		of x in the list and returns
*     		that value.
*/
int lst_count(LIST *l, ElemType x) {
    
    NODE *pTemp = l->front;
    int counter = 0;
    if (pTemp == NULL)
        return 0;
    
    if (pTemp->next == NULL)
        return 1;
    
    while (pTemp != NULL){
        
        if (pTemp->val == x)
            counter++;
        
        
        pTemp = pTemp->next;
        
    }
    
    return counter;
}


/* These are "sanity checker" functions that check to see
*     list invariants hold or not.
*/

int lst_sanity1(LIST *l) {
    if(l->front == NULL && l->back != NULL){
        fprintf(stderr, "lst_sanity1 error:  front NULL but back non-NULL\n");
        return 0;
    }
    if(l->back == NULL && l->front != NULL){
        fprintf(stderr, "lst_sanity1 error:  back NULL but front non-NULL\n");
        return 0;
    }
    return 1;
}

int lst_sanity2(LIST *l) {
    if(l->back != NULL && l->back->next != NULL) {
        fprintf(stderr, "lst_sanity2 error:  back elem has a non-NULL next?\n");
        return 0;
    }
    return l->back->val;
}

/*
*   makes sure that the back pointer is also the last reachable
*    node when you start walking from front.
*    HINT:  use pointer comparison
*/
int lst_sanity3(LIST *l) {


    NODE* temp = l->front;
    if (l->front == NULL){
	return lst_sanity1(l);	
    }

    if (l->back->next != NULL){
	printf("\nl->back->next is non NULL. Reassigning back to point to the last node now...\n");
    }
    else{
        return 1;
    }
    while (temp->next != NULL)
	temp = temp->next;    
    
    if (temp->next == NULL)
	l->back = temp;

    printf("\nlst_sanity3 complete. The back should be pointing to the last node.\n");
    
    
    return 1;
}



ElemType lst_pop_front(LIST *l) {
    ElemType ret;
    NODE *p;
    
    
    if(lst_is_empty(l))
        return DEFAULT;   // no-op
    
    ret = l->front->val;
    l->count_size--;
    if(l->front == l->back) {  // one element
        free(l->front);
        l->front = NULL;
        l->back = NULL;
    }
    else {
        p = l->front;  // don't lose node being deleted
        l->front = l->front->next;  // hop over
        free(p);
    }
    return ret;
}





/* TODO
*
*    if list is empty, we do nothing and return arbitrary value
*    otherwise, the last element in the list is removed and its
*      value is returned.
*
*/
ElemType lst_pop_back(LIST *l) {
    
    ElemType ret;
    NODE* pTemp = l->front;
    
    if (lst_is_empty(l))
        return DEFAULT;
    
    l->count_size--;
    if (l->front->next == NULL){ // Only 1 in the list, so we delete it and return the val in the front
        ret = l->front->val;
        free(l->front);
        l->front = NULL;
        l->back = NULL;
        return ret;
    }
    
    while (pTemp->next->next != NULL){ // Loop that will stop looping on the 2nd to last linked list
        
        pTemp = pTemp->next;
    }
    
    ret = pTemp->next->val; 	// Store the value we will be deleting
    pTemp->next = pTemp->next->next; // Assign the next pointer to point to null
    free(l->back);			// SInce we are deleting the last node we can free l->back as it is pointing to it.
    l->back = pTemp;		// Reassign l->back to pTemp, the new back of the list.
    
    
    return ret;
}

/* TODO
*  For full credit, you cannot allocate any new memory!
*
* description:  self-evident
*/
void lst_reverse(LIST *l) {
    
    //If list is empty, return.
    if (l->front == NULL){
        printf("List is empty\n");
        return;
    }
    
    //List has 1 node.
    if (l->front->next == NULL){
        printf("List has 1 element. It's vacuously trrue to say it's in reverse order.\n");
        return;
    }
    
    
    
    NODE* current = l->front;
    NODE* previous = NULL;
    NODE* next = current->next;
    l->back = l->front;
    
    while (current !=NULL){
        
        next = current->next; // Next always will point to the next node in list
        current->next = previous; // We reassign the next pointer to point to the previous so we can go backwards
        previous = current;   // We reassign previous to the current because that will be the new previous node
        current = next;   // We assign current to move/step forward through the list
        
    }
    
    l->front = previous; // SInce current is now pointing to NULL, we reassign it the previous term which was the node just before hitting NULL
    current = l->front; // Not really needed, but we reassign current to point to the front.
    
}


/*
* removes first occurrence of x (if any).  Returns
*   0 or 1 depending on whether x was found
*/
int lst_remove_first(LIST *l, ElemType x) {
    NODE *p;
    NODE *tmp;
    
    if(l->front == NULL) return 0;
    if(l->front->val == x) {
        lst_pop_front(l);
        return 1;
    }
    // lst non-empty; no match on 1st elem
    p = l->front;
    
    while(p->next != NULL) {
        if(x == p->next->val) {
            tmp = p->next;
            p->next = tmp->next;
            if(tmp == l->back)
                l->back = p;
            free(tmp);
            l->count_size--;
            return 1;
        }
        p = p->next;
    }
    return 0;
}




int lst_remove_all_slow(LIST *l, ElemType x) {
    int n=0;
    while(lst_remove_first(l, x))
        n++;
    return n;
}

/** TODO
 * function: lst_sra_bad_case (sra:  slow_remove_all)
 *
 * description: constructs a list of length n such that
 * the above function takes quadratic time to remove
 * all occurrences of a specified value.
 *
 * By convention, the specified value will be 0
 */
LIST *lst_sra_bad_case(int n) {
    
    // Since by convention we are specifying the value to be 0, if our linked list has anything but non-zeroes in the front and the zeroes in the back, we can create the "worst case" scenario.
    
    LIST* newList = lst_create();
    int i = 0;
    
    for (i = 0; i < n/2; i++)
        lst_push_front(newList, 1); //We can do this multiple of ways, here's one way to do it.
    
    for (i = 0; i < n - n/2; i++) //Here we do n- n/2 in the case when we have an odd number.
        lst_push_back(newList, 0);
    
    return newList;
    
}

// TODO
// desc:  see header file
int lst_remove_all_fast(LIST *l, ElemType x) {
    
    
    NODE *tmp;
    NODE *current;
    NODE *previous = l->front;
    int counter = 0;
    
    if(l->front == NULL) return 0;              // If the list is empty, return 0
    
    current = l->front;                         // Assign the current node we look at to the front of the list
    
    while (current == l->front && current != NULL && current->val == x){    // while loop to check to see if the node(s) are at the front of the list
        
        tmp      = current;                     // if there is a match, we hold that node in our temp node
        current  = current->next;               // We move one over, assigning the current node to the next node.
        l->front = current;                     // We then shift our l->front to point to our new head of the list
        previous = l->front;                    // Have previous point to the first node of list again
        l->count_size--;
        counter++;                              // Increment as we are about to delete ElemType x
        free(tmp);                              // Delete the node
    }
    
    
    while (current != NULL){                    // Main component that handles the body of the linked list and the end.
        
        if (current->val == x){                 // If the node we are looking at has a match go through the body
            
            previous->next = current->next;     // We assign previous->next to point to the next node over
            tmp            = current;           // We hold the node we are about to delete in our tmp node
            current        = current->next;     // We then assign current to move to the next node to compare
            free(tmp);                          // We delete the link to our the node we want to eliminate from the list
            counter++;                          // Add a counter
            l->count_size--;
        }
        
        else{// If we did not find a match with our current->val and x, we store that node in previous, then move current to the next node over.
            previous = current;
            current  = current->next;
            
        }
    }
    return counter;
}

LIST *rm_all(LIST *l, int x){

 NODE *temp = l->front;
 helper_func5(temp, x);
}

NODE *helper_func5( NODE *t, int x){

  if (t == NULL)
	return;


  if (t->val == x && t->next == NULL){
	free(t);
	return;
  }
  if (t->val == x){
     
     NODE *temp2 = t;
     t = t->next;
     helper_func5(t, x);
     free(temp2);  

  }
  else{
   
     helper_func5(t->next, x);  

  }


  return t;


}


/*
 * Helper function that is used to determine if it is sorted in ASCENDING ORDER
 */
int is_sorted_helper(NODE *HELP, int *j){
    
    if (HELP->next == NULL){            // Base case. Once the next value is NULL, you have compared all your elements.
        return *j;
    }
    if (HELP->val >= HELP->next->val){  // Go through the list and determine if the current node you are looking at is greater than or equal to the next node value
        HELP = HELP->next;              // Move the pointer you are looking at next one over.
        is_sorted_helper(HELP, j);      // Go through the function again
        (*j)++;                         // Add 1 to the tally counter each time you pass through this if statement.
    }
    else{
        return 0;
    }
    
    return *j;                          // Return whatever the value of j is.
}


/*
 * Helper function that is used to determine if it is sorted in DESCENDING ORDER.
 * The comments above should help illustrate what is happening here as well
 */
int is_sorted_helper_two(NODE *HELP, int *j){
    
    if (HELP->next == NULL)
        return *j;
    
    if (HELP->val <= HELP->next->val){
        is_sorted_helper_two(HELP->next, j);
        (*j)++;
    }
    else{
        return 0;
    }
    return *j;
}

// TODO
int lst_is_sorted(LIST *l){
    
    NODE *temp = l->front;
    int i = 0;              // Counter for how many nodes we are working with.
    int tally1 = 0;         // Tally1 is used to count how many matches we had going through our recursive helper function.
    int tally2 = 0;         // Tally2 is used to count how many matches we had going through our recursive helper function.
    
    if (l->front == NULL){
        return 1;           // List is empty.
    }
    if (temp->next == NULL){
        return 1;           // 1 element in list so it must be sorted.
    }
    
    while (temp != NULL){   // Loop to count how many nodes we have
        temp = temp->next;
        i++;
    }
    temp = l->front;        // Reassign temp to be the front of the list.
    
    // Checks to see if the list is sorted in ascending or descending. Returns # of correct comparisons
    is_sorted_helper(temp, &tally1);
    
    if (tally1 != i - 1){
        is_sorted_helper_two(temp, &tally2);
    }
    
    // If there weren't exactly nodes - 1 matches, then they are not sorted.
    // A linked list that is, 1, 2, 3, 4 will compare 3 times. Namely, 1 with 2, 2 with 3, and 3 with 4.
    if (tally1 == i-1 || tally2 == i-1){
        printf("Congratulations. Your linked list is sorted.\n");
        return 1;
    }
    else{
        printf("Sorry. The linked list is not sorted. Please sort.\n");
    }
    return 0;
}

/** TODO
* function:  lst_insert_sorted
*
* description:  assumes given list is already in sorted order
*	   and inserts x into the appropriate position
* 	   retaining sorted-ness.
* Note 1:  duplicates are allowed.
*
* Note 2:  if given list not sorted, behavior is undefined/implementation
* 		dependent.  We blame the caller.
* 		So... you don't need to check ahead of time if it is sorted.
*/
void lst_insert_sorted(LIST *l, ElemType x) {
    
    
    NODE *temp = l->front;
    NODE *p = malloc(sizeof(NODE));
    p->val = x;
    
    // If list empty, push a new node into list.
    if (l->front == NULL){
        
        lst_push_front(l, x);
        return;
    }
    
    // If the front is greater than the back, then it is in decending order.
    if (l->front->val >= l->back->val){
        
        // If x is greater than the front, then you have to push to the front.
        if (x >= l->front->val){
            lst_push_front(l, x);
            return;
        }
        
        // If x is less than the back, since it's in decending order, we push back
        else if (x <= l->back->val){
            lst_push_back(l, x);
            return;
        }
    }
    
    // If the front is less than the back, it's in ascending order.
    if( l->front->val <= l->back->val){
        
        // If x is greater than the back, push back so the biggest number is in the end.
        if (x >= l->back->val){
            lst_push_back(l, x);
            return;
        }
        
        // If x is less than the front, then push front, so the list has the smallest value
        else if (x <= l->front->val){
            lst_push_front(l, x);
            return;
        }
        
    }
    
    
    
    
    /*
     * while loop that handles the case for the inner part of the link list (after it first checks the left and right most boundaries.
     */
    while (temp->next != NULL){
        if ( (temp->val <= x) && (temp->next->val >= x) ){
            p->next = temp->next;
            temp->next = p;
            l->count_size++;
            break;
        }
        
        else if ( (temp->val >= x) && (temp->next->val <= x) ){
            p->next = temp->next;
            temp->next = p;
            l->count_size++;
            break;
        }
        temp = temp->next;
    }
}

/** TODO
 * function:  lst_merge_sorted
 *
 * description:  assumes both list a and b are in
 * 	sorted (non-descending) order and merges them
 * 	into a single sorted list with the same
 * 	elements.
 *
 * 	This single sorted list is stored in a while
 * 	b becomes empty.
 *
 * 	if either of given lists are not sorted,
 * 	we blame the caller and the behavior is
 * 	implementation dependent -- i.e., don't worry
 * 	about it!
 *
 * 	Example:
 *
 * 		a:  [2 3 4 9 10 30]
 * 		b:  [5 8 8 11 20 40]
 *
 * 		after call on (a,b)
 *
 * 		a:  [2 3 4 5 8 8 9 10 11 20 30 40]
 * 		b:  []
 *
 * implementation:  should not allocate ANY new list
 * 	nodes -- it should just re-link existing
 * 	nodes.
 *
 * 	Must be linear time in the |a|+|b| -- i.e.,
 * 	the total number of elements being processed.
 */

void lst_merge_sorted(LIST *a, LIST *b){
    
    
    NODE *current_a = a->front;
    NODE *current_b = b->front;
    NODE *holder_b = NULL;
    int size = 0;
 
    // If the list of a is empty and list b is not empty, there is a lot of "book keeping" items we need to accomplish here. Variable names are written in a way to better understand such updates.   
    if (a->front == NULL && b->front != NULL){
        printf("The first list is empty. Pointing the head of first list to the second list.\n");
        a->front = b->front;
        a->back = b->back;
        b->front = NULL;
        b->back  = NULL;
        size = lst_length(b);
        a->count_size = size;
        return;
    }
    
    if (a->front == NULL && b->front == NULL){
        printf("Link lists are empty. Cannot merge sort.\n");
        return;
    }
    if (a->front != NULL && b->front == NULL){
        printf("Your second list is empty. No sort required\n");
        return;
    }
    
    size = lst_length(b);
    
    while (current_a->next != NULL && current_b != NULL){                   // Loop that will go until it reaches the last node.
        
        if (current_a->val >= current_b->val && current_a == a->front){     // First compare to see if we need to pop to the front of list a.
            
            holder_b        = current_b->next;       // Hold the next node of b so we make that the new head of list b.
            a->front        = current_b;             // Set the new front of list a to the one we are pushing in front
            current_b->next = current_a;             // Set the front of the list to point to the old front of the list of a.
            current_a       = a->front;              // Reset the pointer current_a to be at the front of the list.
            current_b       = holder_b;              // Set the head of the list of b to the new node
            b->front        = current_b;             // Likewise with the above comment
        }
        if (current_a->val <= current_b->val && current_a->next->val >= current_b->val){   // Compare to see if we need to place the node in-between values of a.
            
            holder_b        = current_b->next;        // Hold the next node of b so we make that the new head of list b.
            current_b->next = current_a->next;        // Set the new node to point to the next node in list a
            current_a->next = current_b;              // Set the old current node to point to the new node being placed.
            current_b       = holder_b;               // Set the new head of the list of b to the next value.
        }
        
        current_a       = current_a->next;        // If it didn't already shift current_a to the next node, do so here.
    }
    
    
    
    if (current_a->next == NULL){                     // This helps us in the case where if list a is shorter than list b, connect the NULL node to continue with list b.
        
        current_a->next = current_b;
        a->back = b->back;
    }
    
    
    a->count_size = a->count_size + size;
    b->front = NULL;                                  // Set front/back of list b to NULL since we've merged it into list a
    b->back  = NULL;
}

/**
*
* function:  lst_clone
*
* description:  makes a "deep copy" of the given list a
*   and returns it (as a LIST pointer).
*
*/
LIST * lst_clone(LIST *a) {
    
    LIST *deep_copy = lst_create();
    NODE* temp = a->front;
    
    
    if (a->front == NULL)
        printf("List is empty. What are you copying?!\n");
    
    // Since we start at the front of the list, we want to push back to our newList so we get the correct order.
    while (temp != NULL){
        
        lst_push_back(deep_copy, temp->val);
        
        temp = temp->next;
    }
    
    
    return deep_copy;
    
}



/**
*
* function:  lst_from_array
*
* description:  creates a new list populated with the
*      elements of array a[] in the same order as
*      they appear in a[] (element at a[0] will be the
*      first element in the list and so-on).  List is
*      returned as a LIST pointer.
*
*      Parameter n indicates the length of the given array.
*
* runtime requirement:  THETA(n)
*/
LIST * lst_from_array(ElemType a[], int n){
    
    LIST * newList = lst_create();
    int i = 0;
    
    // Since we are pushing to the front, we go through the array from the last element to the first.
    for (i = n-1; i >= 0; i--){
        
        lst_push_front(newList, a[i]);
    }
    
    return newList;
}


/**
*
* function:  lst_to_array
*
* description:  allocates an array of ElemType and populates
*         it with the elements in the given list (as with
*         lst_from_array elements are in the same order in
*         both data structures).
*
* runtime requirement:  THETA(n)
*
*/
ElemType * lst_to_array(LIST *lst) {
    
    NODE *temp = lst->front;
    int counter = 0;
    int  i = 0;
    
    // If list empty, return.
    if ( temp == NULL)
        return;
    
    // Traverse through loop to figure out size of it.
    while (temp != NULL){
        
        counter++;
        temp = temp->next;
    }
    
    // Dynamically allocate memory for an array that is the size of how many nodes in list
    ElemType* newArray = (ElemType*) malloc (sizeof(ElemType)*counter);
    
    // Reset temp to point to the head of the list.
    temp = lst->front;
    
    // Go back through the list and store the values into the array and return it.
    while (temp != NULL){
        
        newArray[i] = temp->val;
        i++;
        temp = temp->next;
        
    }
    
    
    return newArray;
}


/**
*
* function:  lst_prefix
*
* description:  removes the first k elements from the
*               given list which are used to form a new list
*		which is then returned.
*
*		if n is the length of the given list, we have the
*		following boundary conditions:
*
*		  if k==0:
*			lst unchanged and an empty list returned
*		  if k>=n:
*			lst becomes empty and a list containing
*			all elements previously in lst is returned.
*
*		examples:
*
*		  EX1:  lst:  [2, 3, 9, 7, 8]
*			k:    3
*
*			after call:
*			   lst:  [7, 8]
*			   returned list:  [2, 3, 9]
*
*		  EX2  lst:  [2, 3, 9, 7, 8]
*			k:    0
*
*			after call:
*			   lst:  [2, 3, 9, 7, 8]  (unchanged)
*			   returned list:  []
*
*		  EX3  lst:  [2, 3, 9, 7, 8]
*			k:    5
*
*			after call:
*			   lst:  []
*			   returned list:  [2, 3, 9, 7, 8]
*
* REQUIREMENTS:
*
*	RUNTIME:  THETA(n) worst case where n is the length of the given list
*
*       ORDERING:  the ordering of the returned prefix should be the same as
*                  in the given list
*
*       MEMORY:    for full credit, no new nodes should be allocated or deallocated;
*		   you should just "re-use" the existing nodes.  HOWEVER, you will
*		   need to allocate a LIST structure itself (i.e., for the returned
*		   list).
*/
LIST * lst_prefix(LIST *lst, unsigned int k) {
    
    LIST *newList = lst_create();
    NODE *temp_lst = lst->front;
    NODE *temp_newList = newList->front;
    int count = 0;
    int i = 0;
    
    // List is empty
    if (temp_lst == NULL){
        return;
    }
    
    
    //If there is only 1 node in the list and our k value is greater than one, remove it from the list and update the size.
    if (temp_lst -> next == NULL && k >= 1){
        
        newList->front = temp_lst;
        newList->back = temp_lst;
        lst->front = NULL;
        lst->back = NULL;
	lst->count_size = 0;
	newList->count_size = 1;
        return newList;
    }
    
    
    // Traverse through the list, find how big the list is, assign the back of newList to the back of the old list.
    while (temp_lst != NULL){
        count++;
        newList->back = temp_lst;
        temp_lst = temp_lst->next;
    }
    
    // If k is 0, we don't really need to do anything here
    if (k == 0){
        newList->front = NULL;
        newList-> back = NULL;
        return newList;
    }
    
    // If k is larger than the count (total size of the node), "transfer" the entire list to the newList.
    else if (k >= count){
        newList->front = lst->front;
        lst->front = NULL;
        lst->back = NULL;
    }
    
    else{
        // if k is less than count, we take the head our old list and have our newList point to that.
        temp_lst = lst->front;
        newList->front = lst->front;
        temp_newList = newList->front;
        
        // Since k is a fraction of what count is, we create a loop to take the k first nodes from the list and store into
        // our newlist and return that.
        for (i = 0; i < k; i++){
            temp_newList = temp_lst;
            temp_lst = temp_lst->next;
            newList->back = lst->front;
            
            lst->front = temp_lst;
        }
        newList->back->next = NULL;
    }
	
	// Updating the lengths of both list here. I avoided any updates in the above code to ensure everything worked accordingly.
	lst->count_size = lst->count_size - k;
	newList->count_size = k;
    
    
    return newList;
    
}




/**
*
* function:  lst_filter_leq
*
* description:  removes all elements of the given list (lst) which
*		are less than or equal to a given value (cutoff)
*
*		A list containing the removed elements is returned.
*
* examples:
*
*	EX1: 	lst:  [4, 9, 2, 4, 8, 12, 7, 3]
*		cutoff:  4
*
*		after call:
*			lst:  [9, 8, 12, 7]
*			returned list:  [4, 2, 4, 3]
*
*       -----------------------------------------
*	EX2: 	lst:  [6, 5, 2, 1]
*		cutoff:  6
*
*		after call:
*			lst:  []
*	 		returned list:  [6, 5, 2, 1]
*
* REQUIREMENTS:
*
*	RUNTIME:  THETA(n) where n is the length of the given list
*
*       ORDERING:  the ordering of the returned list should be the same as
*                  in the given list
*
*       MEMORY:    for full credit, no new nodes should be allocated or deallocated;
*		   you should just "re-use" the existing nodes.  HOWEVER, you will
*		   need to allocate a LIST structure itself (i.e., for the returned
*		  list).
*
*/
LIST * lst_filter_leq(LIST *lst, ElemType cutoff) {
    
    NODE* walker = lst->front;		// Walker that walks through our original
    NODE* previous = lst->front;	// Holds the previous of our original
    NODE* next = lst->front;		// Holds the next of our original
    int count = 0;
    LIST* newList = lst_create();
    NODE* newTemp = newList->front; //Temp holder or "walker" for our new list
    
    
    // If list is empty, return newList.
    if (lst->front == NULL)
        return newList;
    
    // If only 1 element in list and it meets the cutoff, transfer into new list.
    if (lst->front->next == NULL){
        
        if (lst->front->val <= cutoff){
            
            newList->front = lst->front;
            newList->back = lst->back;
            lst->front = NULL;
            lst->back = NULL;
        }
    }
    
    
    
    while (walker != NULL){
        
        //If we traverse through the linked list and meets the cutoff.
        if (walker->val <= cutoff){
            
            count++;                    // Simple counter to make sure we store the front of the list correctly for the newList.
            
            if (count == 1){            // We assign the front of the list to our new list when the counter is 1.
                newList->front = walker;
                newTemp = newList->front;
            }
            
            //If the front of the list we are working with meets the cutoff, we reassign where the front of the list is and transfer that node to the newList.
            if (lst->front->val <= cutoff){
                
                newTemp = lst->front;
                lst->front = lst->front->next;
                walker = lst->front;
                previous = lst->front;
                next = lst->front;
                
            }
            
            // If it's a node that is in the middle of the list, extract the new node to the newList
            else if (walker->val <= cutoff){
                
                previous->next = walker->next;
                newTemp->next = walker;
                newTemp = walker;
                walker = walker->next;
            }
        }
        
        // If there was no match with the cutoff, traverse through the list.
        else{
            previous = walker;
            walker = walker->next;
        }
    }
    
    //If there was 1 or more nodes that met the cutoff, set the back of the newList to wherever the program left off at.
    if (count >= 1)
    {
        newList->back = newTemp;
        newList->back->next = NULL;
    }
    return newList;
}

/**
* TODO
* function:  lst_concat
*
* description:  concatenates lists a and b; resulting
*    concatenation is reflected in list a; list b becomes
*    empty.
*
*    example:
*
*	EX1:  a: [2, 9, 1]
*	      b: [5, 1, 2]
*
*	after call:
*
*		a: [2, 9, 1, 5, 1, 2]
*		b: []
*
* REQUIREMENTS:
*
*     runtime:  O(1)
*
*     sanity:  this operation makes sense when a and b
*		are distinct lists.  For example, we don't
*		want/allow the caller to do something like
*		this:
*
*			LIST *my_list;
*
*			lst_push_front(my_lst, 4);
*			lst_push_front(my_lst, 2);
*
*			lst_concat(my_lst, my_lst);
*
*		your implementation must detect if it is being
*		called this way.  If so the function does nothing
*		and (optionally) prints an error message to
*		stderr.
*
*/
void lst_concat(LIST *a, LIST *b) {
    
    
    if (a->front == b->front){
        printf("The lists are the same. Try again. \n");
        return;
    }
    
    //List is empty, so point to b list. We also need to update the count size of a.
    if (a->front == NULL){
        a->front = b->front;
        a->back = b->back;
	a->count_size = b->count_size;
        return;
    }
    if (b->front == NULL)
	return;
    
     
    // List the back of a to point to b and then you're done! Easy! (Don't forget to update the size!).
    a->back->next = b->front;
    a->back = b->back;
    a->count_size = a->count_size + b->count_size;
    b->front = NULL;
    b->back = NULL;
    
}


NODE *remove_all_X1(NODE *lst, int x){


//NODE *temp;

if(lst->next == NULL)
	return lst;


if (lst->next->val == x){
	NODE* temp = lst->next;
	lst->next = lst->next->next;
	free (temp);
	while (lst->next->val == x){
	temp = lst->next;
	lst->next = lst->next->next;
	free(temp);
	}
	remove_all_X1(lst->next, x);
}

else{
remove_all_X1(lst->next, x);
}

//return lst;

}


LIST *remove_all_x(LIST *lst, int x){



NODE *temp = lst->front;
remove_all_X1(temp, x);
lst_print(lst);



}
