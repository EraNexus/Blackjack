# src makefile
# compiles .cpp files in src directory

CXX = g++
CXXFLAGS = -Wall -g -Iinc
TARGET = Blackjack
SRCDIR = src
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

# links object files
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# runs executable
run: $(TARGET)
	./$(TARGET)

# clean rule
clean:
	rm -f $(OBJS) $(TARGET)