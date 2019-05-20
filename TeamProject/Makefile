-include config.mk

all: libjson.a 

libjson.a: json.o parser.o
	$(AR) rc $@ $^

%.o: %.c json.h
	$(CC) -c $(CFLAGS) $< -o $@

parser: parser.o libjson.a
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	rm -f json.o
	rm -f libjson.a
	rm -f parser
.PHONY: all clean test
