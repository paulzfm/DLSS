SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:%.cpp=%.o)
TARGET = dlss

all: $(TARGET)
$(TARGET): $(OBJECTS)
	g++ $(OBJECTS) -o $(TARGET)
%.o: %.cpp $(HEADERS)
	g++ -c $< -o $@
clean:
	rm *.o *~ $(TARGET)