LIBS =
INCLUDES = -I./include/
CC = gcc -std=c11
CPPFLAGS = -lpthread
CXXFLAGS =
EXECUTABLE = t1

SRC_DIR = src

SRCS += $(wildcard $(SRC_DIR)/*.c)

OBJS += $(SRCS:.cpp=.o)

%.o: %.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -O0 -Wall -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

all:	$(OBJS)
	$(CC) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJS) $(LIBS) $(CPPFLAGS) 
	@echo 'Build complete!'
	@echo ' '

test:	all
	@echo 'Executing tests...'
	./$(EXECUTABLE)
	@echo 'Done!'

clean:
	rm -rf ./$(SRC_DIR)/*.o $(EXECUTABLE)
