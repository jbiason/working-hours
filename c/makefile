DEPS = hours.o period.o

wh: main.o $(DEPS)
	gcc $^ -o $@

%.o: %.c %.h
	gcc -c $< -Wall

.PHONY: test
test: wh_tests
	./wh_tests
	rm ./wh_tests

wh_tests: wh_tests.o $(DEPS)
	gcc $^ -o $@
