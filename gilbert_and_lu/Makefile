CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Iinclude

SRCS = src/main.cpp src/menu.cpp src/tests.cpp
OBJS = $(SRCS:.cpp=.o)
HDRS = $(wildcard include/*.h)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

src/%.o: src/%.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
