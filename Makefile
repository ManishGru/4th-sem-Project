TARGET = MAZESOLVER
CXX= g++
CXXFLAGS= -lncurses -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -static

CXX_SOURCES = \
src/Camera.cpp \
src/EBO.cpp \
src/glad.c \
src/shaderClass.cpp \
src/stb.cpp \
src/Texture.cpp \
src/VAO.cpp \
src/VBO.cpp \
src/cube.cpp \
main.cpp

all: $(CXX_SOURCES)
	$(CXX) $(CXX_SOURCES) $(CXXFLAGS) -o $(TARGET).out

run: 
	./$(TARGET).out
	
clean:
	rm -rf $(TARGET).out
