files = main.c aovnet.c

maintest: $(files)
	gcc -g $^ -o $@

main: $(files)
	gcc -o $@ $^
