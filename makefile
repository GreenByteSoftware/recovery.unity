TARGET = recover_unity
CC = gcc
CFLAGS = -g -Wall

.PHONY: default all clean

default: $(TARGET)
all: default

OBJDIR = obj
SRCDIR = src
_OBJ = vector_comp.o vector_str.o hierarchy_browser.o main.o
OBJECTS = $(patsubst %,$(OBJDIR)/%,$(_OBJ))
_HEAD = vector_comp.h vector_str.h types.h hierarchy_browser.h
HEADERS = $(patsubst %,$(SRCDIR)/%,$(_HEAD))

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
		$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
		$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
		-rm -f $(OBJDIR)/*.o
		-rm -f $(TARGET)
