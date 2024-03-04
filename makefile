# Variables
CXX = g++
CXXFLAGS = -Wall -std=c++11 -g
LIBS = -lglfw -lGLEW -lGL
SRCDIR = src
INCLUDES = -I$(SRCDIR) -Iglm

SRC = $(wildcard $(SRCDIR)/*.cpp)

OBJ = $(addprefix build/, $(notdir $(SRC:.cpp=.o)))
EXEC = build/modelViewer.exe

# Default target
all: $(EXEC)

# Create the build directory
build:
	mkdir -p build

# Linking
$(EXEC): $(OBJ)
	$(CXX) $^ -o $@ $(LIBS)

# Compiling
build/%.o: $(SRCDIR)/%.cpp | build
	$(CXX) $(INCLUDES) -c $< -o $@ $(CXXFLAGS)

# Cleaning up
clean:
	rm -rf build	