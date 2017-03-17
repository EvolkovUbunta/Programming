CC=gcc
LD=gcc
CXX=g++
C_FLAGS=-O0 -g

TARGET=calc

OBJS=calc.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(OBJS) -o $(TARGET) -ldl

%.o: %.c
	$(CC) $(C_FLAGS) -c $^

%.o: %.cpp
	$(CXX) $(C_FLAGS) -c $^

clean:
	rm -rf $(TARGET) $(OBJS)
