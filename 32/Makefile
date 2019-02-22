CFLAGS=-Wall -Werror -std=gnu99 -pedantic -ggdb3
OBJS=kv_test.o kv.o
PROGRAM=kv_test
# $(PROGRAM): $(OBJS)
#         gcc $(CFLAGS) -o $@ $(OBJS)

# %.o: %.c kv.h
#         gcc -c $(CFLAGS) $<

# .PHONY: clean
# clean: 

# clean:
#         rm -f $(OBJS) $(PROGRAM) *~

$(PROGRAM): $(OBJS)
	gcc $(CFLAGS) -o $@ $(OBJS)

%.o: %.c kv.h
	gcc -c $(CFLAGS) $<

clean:
	rm -f $(OBJS) $(PROGRAM) *~
