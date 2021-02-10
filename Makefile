CC 	 = gcc
CFLAGS   = -std=c11 -w
TARGET   = doenv
OBJFILES =
SOURCE = doenv.c
  
$(TARGET): $(OBJFILES)  
	$(CC) -o $(TARGET) $(SOURCE) $(CFLAGS) 

clean: 
	rm -f $(TARGET) *.o
