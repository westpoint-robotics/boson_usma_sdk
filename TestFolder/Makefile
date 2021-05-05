# the compiler: gcc for C program, define as g++ for C++
CC = g++

INCLUDES = -I /usr/local/include/boson
LFLAGS += -L /usr/local/lib
LIBS = -lboson

# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings
CFLAGS  = -g -Wall ${INCLUDES}

# The build target 
TARGET = bosontest

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp $(LFLAGS) $(LIBS) 

clean:
	$(RM) $(TARGET)
	

gcc -I/usr/local/include/boson bosontest.cpp /usr/local/lib/libboson.so /usr/local/lib/libboson.so /home/user1/Projects/ConvergenceCamera/convergence_camera/BosonSDK/FSLP_Files/FSLP_64.so -o bosontest -lstdc++

