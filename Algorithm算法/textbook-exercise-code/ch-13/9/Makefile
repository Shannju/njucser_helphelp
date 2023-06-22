EXEC = 13-9 

$(EXEC): main.c
	gcc -ggdb3 main.c -o $(EXEC)

debug: $(EXEC)
	gdb $(EXEC)

run: $(EXEC)
	./$(EXEC)

clean:
	rm -rf $(EXEC)
