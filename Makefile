CC = g++
CVFLAG = `pkg-config --cflags --libs opencv`
#BOOSTFLAG = -I/opt/local/include/ -I/usr/local/include/ -L/opt/local/lib/ -lboost_serialization -lboost_filesystem -lboost_system

SRCS = main.cpp Node.cpp Tree.cpp Forest.cpp
TARGET = rf

all:
	$(CC) -o $(TARGET) $(SRCS) 
#$(CVFLAG) 
#$(BOOSTFLAG)