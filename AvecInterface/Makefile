CC=gcc
CFLAGS=-Wall
LIBS=`pkg-config --libs-only-other --libs-only-L MLV` `pkg-config --libs-only-l MLV`
SRC_DIR=src
SRCS=$(wildcard $(SRC_DIR)/*.c)
TARGET=tetriste

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(shell pkg-config --cflags MLV) -o $@ $^ $(LIBS)

clean:
	rm -f $(TARGET)


