CC = g++
CFLAGS = -pedantic-errors -std=c++11 -g
LIBS = -lncurses
SRCS = main.cpp display.cpp rocket.cpp scoreboard.cpp
OBJS = $(SRCS:.cpp=.o)
FILES = scores
TARGET = rocket

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) $(FILES)
