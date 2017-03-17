CC=gcc
LD=g++
CXX=g++
C_FLASGS=-O0 -g

TARGET=libexample-plugin-2.so

OBJS=calc.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) --shared $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(C_FLAGS) -fPIC -c $^

%.o: %.cpp
	$(CXX) $(C_FLAGS) -fPIC -c $^

clean:
	rm -rf $(TARGET) $(OBJS)
