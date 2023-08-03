CC=clang
CC_FLAG=-Wall -Wextra
CC_FLAG_DEBUG=-g -fsanitize=address
CC_FLAG_RELEASE=-O3

SRC=src
BUILD=build

C_SOURCES=$(wildcard $(SRC)/*.c)
MAIN=main
INSTALL_NAME=cgen
INSTALL_DIR=/usr/local/bin

all: make_dir compile

compile:
	$(CC) $(C_SOURCES) $(CC_FLAG) $(CC_FLAG_DEBUG) -o $(BUILD)/$(MAIN)

make_dir:
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD) app

run:
	$(BUILD)/$(MAIN)

release:
	$(CC) $(C_SOURCES) $(CC_FLAG) $(CC_FLAG_RELEASE) -o $(BUILD)/$(MAIN)

install:
	cp $(BUILD)/$(MAIN) $(BUILD)/$(INSTALL_NAME)
	install -m 755 $(BUILD)/$(INSTALL_NAME) $(INSTALL_DIR)
