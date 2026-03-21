CXX = clang++
CXXFLAGS = -std=c++17 -Wall

SRCS = main.cpp menu.cpp gauss_method.cpp LU_decompozition.cpp matrixes.cpp tests.cpp default_gauss.cpp
OBJS = $(SRCS:.cpp=.o)
HDRS = $(wildcard *.h)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
