CC 	 = gcc
CFLAGS   = -std=c99
TARGET   = doenv
OBJFILES =
  
$(TARGET): $(OBJFILES)  
	$(CC) -o $(TARGET) $(OBJFILES) $(CFLAGS) 

main.o: main.c
	gcc doenv.c -std=c99

clean: 
	rm -f $(TARGET) *.o
