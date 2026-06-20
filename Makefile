.PHONY: clean all install build

# libc++ make clang llvm

CXX = clang++
# CXXFLAGS = -std=c++26 -stdlib=libc++ -O3 -flto -fno-exceptions -march=native -mtune=native -mavx2 -mf16c -mfma -DNDEBUG -pthread
CXXFLAGS = -std=c++26 -stdlib=libc++ -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wshadow -O1 -pthread -D_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_DEBUG
LFLAGS = -lm

TARGET = cruxy
FILES = $(SRC)
OBJ = $(FILES:.cpp=.o)
SRC = $(shell find src -name '*.cpp')

STD_CPPM = /usr/share/libc++/v1/std.cppm
STD_PCM = $(CURDIR)/std.pcm

all: build

build: $(TARGET)
	
$(TARGET): $(OBJ) $(STD_PCM)
	$(CXX) $(CXXFLAGS) -fmodule-file=std=$(STD_PCM) -o $@ $^ $(LFLAGS)

%.o: %.cpp $(STD_PCM)
	$(CXX) $(CXXFLAGS) -fmodule-file=std=$(STD_PCM) -c $< -o $@

$(STD_PCM): $(STD_CPPM)
	$(CXX) $(CXXFLAGS) -Wno-reserved-module-identifier -Wno-reserved-identifier --precompile $^ -o $@

clean:
	rm -f $(OBJ) $(TARGET) $(STD_PCM)
