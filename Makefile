CXX = g++
CXXFLAGS =-std=c++17 -Wall -DGL_SILENCE_DEPRECATION
LDLIBS = -framework OpenGL -framework GLUT

TARGET = bin/game
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:%.cpp=%.o)
INCS = -I./include

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS) $(INCS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

.PHONY: clean tmpclean
clean: tmpclean
	rm -f $(OBJS) $(TARGET)
tmpclean:
	find . -name *~ -exec rm -f {} \;
