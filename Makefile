CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic
TARGET := des
SRC := des.cpp

.PHONY: all clean run test

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

test: $(TARGET)
	bash tests/test_sample.sh

clean:
	rm -f $(TARGET)
	rm -rf build
