CC ?= cc
CFLAGS ?= -std=c23 -Wall -Wextra -Wpedantic
CPPFLAGS += -DPINC_VERSION=\"$(shell cat VERSION)\"

BUILD_DIR := build
TARGET := $(BUILD_DIR)/pinc
SRCS := src/main.c src/pinc_coding/cli.c
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)

PREFIX ?= $(HOME)/.local
BINDIR := $(PREFIX)/bin

.PHONY: all clean install

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

install: $(TARGET)
	install -d $(BINDIR)
	install -m 755 $(TARGET) $(BINDIR)/pinc

clean:
	rm -rf $(BUILD_DIR)
