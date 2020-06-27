OBJS = main.o hours.o

wh: $(OBJS)
	gcc $^ -o $@

%.o: %.c %.h
	gcc -c $< -Wall
