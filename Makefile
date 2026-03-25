CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Igilbert_and_lu/include

SRCS = gilbert_and_lu/src/main.cpp gilbert_and_lu/src/menu.cpp gilbert_and_lu/src/tests.cpp
OBJS = $(SRCS:.cpp=.o)
HDRS = $(wildcard gilbert_and_lu/include/*.h) $(wildcard gilbert_and_lu/include/*.tpp)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

gilbert_and_lu/src/%.o: gilbert_and_lu/src/%.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean

