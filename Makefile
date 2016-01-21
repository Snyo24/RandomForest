CC = g++
CVFLAG = `pkg-config --cflags --libs opencv`
BOOSTFLAG = -I /opt/local/include/boost -L/opt/local/lib/ -lboost_serialization -lboost_filesystem -lboost_system -lboost_random

SRCS = main.cpp Node.cpp Tree.cpp Forest.cpp
TARGET = rf

all:
	$(CC)  -o $(TARGET) $(SRCS) $(CVFLAG) 

clean:
	rm -rf *.o $(TARGET)
#$(BOOSTFLAG)
#