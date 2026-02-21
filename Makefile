CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
CFLAGS_DEBUG = $(CFLAGS) -DDEBUG
LDFLAGS =

SRC_DIR = src
OBJ_DIR = obj
OBJ_DIR_DEBUG = obj_debug
BIN_DIR = bin

SRCS := $(shell find $(SRC_DIR) -type f -name '*.c')

OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
OBJS_DEBUG := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR_DEBUG)/%.o,$(SRCS))

TARGET = $(BIN_DIR)/mvm
TARGET_DEBUG = $(BIN_DIR)/mvm_debug

all: $(TARGET)

debug: $(TARGET_DEBUG)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

$(TARGET_DEBUG): $(OBJS_DEBUG)
	@mkdir -p $(BIN_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c -o $@ $<

$(OBJ_DIR_DEBUG)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS_DEBUG) -MMD -MP -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR) $(OBJ_DIR_DEBUG) $(BIN_DIR)

rebuild: clean all

run: $(TARGET)
	./$(TARGET)

run-debug: $(TARGET_DEBUG)
	./$(TARGET_DEBUG)

-include $(OBJS:.o=.d)
-include $(OBJS_DEBUG:.o=.d)

.PHONY: all clean rebuild run debug run-debug
