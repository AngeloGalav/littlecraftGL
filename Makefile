CC = g++

RMV = rm -f src/*.o

# freetype flags
FTINCLUDEDIR = -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/harfbuzz -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/stb

DLIBS = usr/lib/
GLFLAGS = -lpthread -lGLU -lglut -lGL -lGLEW -lX11 -lXrandr -lXi -ldl -lfreetype
CFLAGS = $(GLFLAGS) $(FTINCLUDEDIR) -I$(GL_INCLUDE_DIR) -Wall -O0

# executable name (can be modified here)
EXEC_NAME = glCraft

.PHONY : all clean

all : $(EXEC_NAME)

SRC = $(wildcard src/*.cpp) $(wildcard src/**/*.cpp) # WATCH OUT FOR THIS LINE!!!!!!! IT'S UNRECOGNIZED BY MAKE, SO BE SURE IT IS CORRECT!!!
OBJ = $(SRC:.cpp=.o) # considers the files with a suffix 

$(EXEC_NAME) : $(OBJ)
	@echo "** Building main executable, aka $(EXEC_NAME) ..."
	$(CC) -L$(DLIBS) -o $@ $(OBJ) $(CFLAGS)

%.o: %.cpp
	@echo "** Building obj files..."
	$(CC) -c $< -o $@ $(CFLAGS)

clean :
	@echo "** Removing object files..."
	$(RMV)