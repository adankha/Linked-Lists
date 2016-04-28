
ll_tst: llist.o ll_tst.c
	gcc ll_tst.c llist.o -o ll_tst

llist.o: list.h llist.c
	gcc -c llist.c


