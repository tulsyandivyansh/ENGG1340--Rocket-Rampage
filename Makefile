CC = g++
CFLAGS = -pedantic-errors -std=c++11 -g
LIBS = -lncurses
SRCS = main.cpp menu.cpp game.cpp highscore.cpp
OBJS = $(SRCS:.cpp=.o)
FILES = scores
TARGET = breakout

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) $(FILES)
