CXX := g++
CXXFLAGS := -std=c++17 -O2

VENDOR_INCLUDES := \
	-Ithirdparty/ \
	-Ithirdparty/uWebSockets/uSockets/src \
	-Ithirdparty/json/single_include

USOCKETS_DIR := thirdparty/uWebSockets/uSockets
USOCKETS_LIB := $(USOCKETS_DIR)/uSockets.a

LIBS := \
	$(USOCKETS_LIB) \
	-pthread -lz

BIN_DIR := ./bin
TARGET := $(BIN_DIR)/LobbyServer
SRC := LobbyServer/main.cpp

all: $(TARGET)

# Build server (depends on uSockets)
$(TARGET): $(SRC) $(USOCKETS_LIB) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC) $(VENDOR_INCLUDES) $(LIBS) -o $(TARGET)


# Ensure bin directory exists
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Build uSockets if missing or outdated
$(USOCKETS_LIB):
	$(MAKE) -C $(USOCKETS_DIR)

clean:
	rm -rf $(BIN_DIR)
	$(MAKE) -C $(USOCKETS_DIR) clean

.PHONY: all clean
