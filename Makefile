#OBJS specifies which files to compile as part of the project 
OBJS = FlappyBird.c Bird.c Engine.c Pipe.c Score.c json/cJSON.c Text.c
#CC specifies which compiler we're using 
CC = gcc 
#COMPILER_FLAGS specifies the additional compilation options we're using 
# -w suppresses all warnings 
COMPILER_FLAGS = -w -ggdb -std=c11
#LINKER_FLAGS specifies the libraries we're linking against 
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
#OBJ_NAME specifies the name of our exectuable 
OBJ_NAME = flappyBird 
#This is the target that compiles our executable 
all : $(OBJS) 
		$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)