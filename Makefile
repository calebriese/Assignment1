CC 	 = gcc
CFLAGS   = -std=c11 -w
TARGET   = doenv
OBJFILES =
SOURCE = doenv.c
  
$(TARGET): $(OBJFILES)  
	$(CC) -o $(TARGET) $(SOURCE) $(CFLAGS) 

main.o: main.c
	gcc -o doenv doenv.c -std=c11 -w

clean: 
	rm -f $(TARGET) *.o
