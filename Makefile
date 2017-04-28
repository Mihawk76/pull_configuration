# What to call the final executable
TARGET = main_program

# Which object files that the executable consists of
OBJS= main_program.o

# What compiler to use
CC = gcc

# Compiler flags, -g for debug, -c to make an object file
CFLAGS = -c -g

# This should point to a directory that holds libcurl, if it isn't
# in the system's standard lib dir
# We also set a -L to include the directory where we have the openssl
# libraries
LDFLAGS = -L/home/dast/lib -L/usr/local/ssl/lib

# We need -lcurl for the curl stuff
# We need -lsocket and -lnsl when on Solaris
# We need -lssl and -lcrypto when using libcurl with SSL support
# We need -lpthread for the pthread example
LIBS = -lcurl -ljson
MYSQL_LIBS := $(shell mysql_config --libs --cflags)

# Link the target with all objects and libraries
$(TARGET) : $(OBJS)
	$(CC)  -o $(TARGET) $(OBJS) $(LDFLAGS) $(LIBS) $(MYSQL_LIBS)

# Compile the source files into object files
main_program.o : main_program.c
	$(CC) $(CFLAGS) $< $(MYSQL_LIBS)
clean:
	@echo "[Clean]"
	@rm -f $(OBJ) $(TARGET) *~ core tags $(BINS)

