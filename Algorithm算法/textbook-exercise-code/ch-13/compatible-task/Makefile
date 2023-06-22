EXEC = compatible-task  

$(EXEC): main.c
	gcc -ggdb3 main.c -o $(EXEC)

debug: $(EXEC)
	gdb -x init.gdb $(EXEC)

run: $(EXEC)
	./$(EXEC) < testcase.txt

clean:
	rm -rf $(EXEC)
