CFLAGS=-Wall -Werror -std=gnu99 -pedantic -ggdb3
#CFLAGS=-Werror -std=gnu99 -pedantic -ggdb3
OBJS=cards.o main.o deck.o
PROGRAM=main


$(PROGRAM): $(OBJS)
	gcc $(CFLAGS) -o $@ $(OBJS)

%.o: %.c kv.h
	gcc -c $(CFLAGS) $<

clean:
	rm -f $(OBJS) $(PROGRAM) *~