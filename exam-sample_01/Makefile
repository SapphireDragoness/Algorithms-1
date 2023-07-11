CFLAGS += -Wall -Wextra -std=c11 -pedantic
CFLAGS += -g
CFLAGS += -I./include
LDFLAGS += -L./lib
LDLIBS += -lupoalglib -lm


.PHONY: all clean

all: test/bst_predecessor test/bidi_bubble_sort

test/bst_predecessor: test/bst_predecessor.o exam.o

test/bidi_bubble_sort: test/bidi_bubble_sort.o exam.o

clean:
	$(RM) test/bst_predecessor
	$(RM) test/bidi_bubble_sort
	$(RM) *.o test/*.o
