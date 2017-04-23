LIBS = 
INCLUDES = -I./$(BENCHMARK_DIR) -I../include -I../src
CC = g++ 
CPPFLAGS = 
CXXFLAGS = -g -MMD -MP -std=c++11 -lpthread -pthread -DBENCH
EXECUTABLE = bench.out

BENCHMARK_DIR = hayai
SRC_DIR = src
CODE_SRC_DIR = ../src

BENCHMARK_SRC += $(wildcard $(SRC_DIR)/*.cpp)
BENCHMARK_SRC += $(wildcard $(CODE_SRC_DIR)/*.cpp)
OBJS += $(BENCHMARK_SRC:.cpp=.o)
HAYAI_SRC += $(wildcard $(BENCHMARK_DIR)/*.cpp)
HAYAI_OBJS += $(HAYAI_SRC:.cpp=.o)

%.o: %.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	$(CC) $(INCLUDES) $(CPPFLAGS) $(CXXFLAGS)  -O0 -Wall -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

all:	bench $(OBJS)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJS) ./$(HAYAI_OBJS) $(LIBS)
	@echo 'Build complete!'
	@echo ' '
	
bench: ./$(HAYAI_OBJS)

$(HAYAI_OBJS): 

test:	all
	@echo 'Executing tests...'
	./$(EXECUTABLE)
	@echo 'Done!'

clean:
	rm -rf ./$(SRC_DIR)/*.o $(EXECUTABLE)

veryclean: clean
	rm -rf ./$(BENCHMARK_DIR)/*.o