CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra

SRC_DIR = src
TARGET = table_gen

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

all: $(TARGET)

$(TARGET): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf $(TARGET)

.PHONY: all clean
