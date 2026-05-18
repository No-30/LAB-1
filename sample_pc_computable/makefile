# =========================
# User-configurable options
# =========================

APP_NAME += sample_pc_computable
BUILD_DIR += ../../build
SRC_DIR += ../../std
SRC_DIR += $(CURDIR)
CC += gcc
CFLAGS += -Wall -Wextra -O2
LDFLAGS ?=
SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
TARGET := $(BUILD_DIR)/$(APP_NAME)

# =========================
# Default target
# =========================

.PHONY: all
all: $(TARGET)

# =========================
# Build rules
# =========================

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(BUILD_DIR) $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# =========================
# Utility targets
# =========================

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: run
run: $(TARGET)
	./$(TARGET)

.PHONY: debug
debug:
	$(MAKE) CFLAGS="-Wall -Wextra -g -O0"

.PHONY: release
release:
	$(MAKE) CFLAGS="-Wall -Wextra -O3"

# =========================
# Help target
# =========================

.PHONY: help
help:
	@echo "Available targets:"
	@echo "  make            Build project"
	@echo "  LDFLAGS='-lm'"