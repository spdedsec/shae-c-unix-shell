.PHONY: build test release clean install help
CC ?= gcc
CFLAGS = -O2 -std=c11 -Wall -Wextra
SRC = src/shell.c
BIN = shae-shell

build:
	@$(CC) $(CFLAGS) -o $(BIN) $(SRC) -lreadline 2>/dev/null || $(CC) $(CFLAGS) -o $(BIN) $(SRC)

test: build
	@echo "exit" | ./$(BIN)
	@echo "PASS"

release: build
	@tar czf dist/$(BIN)-v0.1.0-src.tar.gz src/ scripts/ Makefile README.md DESIGN.md LICENSE docs/

install: build
	@cp $(BIN) ~/.local/bin/

clean:
	@rm -f $(BIN)
	@rm -rf dist/

help:
	@echo "Targets: build test release install clean help"
