EXEC = 13-5 

$(EXEC): main.c
	gcc -ggdb3 main.c -o $(EXEC)

debug: $(EXEC)
	gdb -x init.gdb $(EXEC)

clean:
	rm -rf $(EXEC)
