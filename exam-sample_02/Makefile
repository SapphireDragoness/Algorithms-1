CFLAGS += -Wall -Wextra -std=c11 -pedantic
CFLAGS += -g
CFLAGS += -I./include
LDFLAGS += -L./lib
LDLIBS += -lupoalglib -lm


.PHONY: all clean

all: test/bst_subtree_count_even test/ht_sepchain_odelete

test/bst_subtree_count_even: test/bst_subtree_count_even.o exam.o

test/ht_sepchain_odelete: test/ht_sepchain_odelete.o exam.o

clean:
	$(RM) test/bst_subtree_count_even
	$(RM) test/ht_sepchain_odelete
	$(RM) *.o test/*.o
