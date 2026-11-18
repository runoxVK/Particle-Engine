# Convenience wrapper around the CMake build.
# CMake (with FetchContent) still does the real work and fetches SDL3.

# Must match the name in project(...) in CMakeLists.txt
# Run paths are quoted with forward slashes so they work in cmd.exe and sh alike
NAME      ?= FallingSand
GENERATOR ?= Ninja

BUILD_DIR   := build
RELEASE_DIR := build-release

ifeq ($(OS),Windows_NT)
    EXE := .exe
else
    EXE :=
endif

.PHONY: all build run release run-release configure clean rebuild

all: build

# Debug build in build/ (this is the one Zed/clangd reads)
$(BUILD_DIR)/CMakeCache.txt:
	cmake -S . -B $(BUILD_DIR) -G "$(GENERATOR)" -DCMAKE_BUILD_TYPE=Debug

configure: $(BUILD_DIR)/CMakeCache.txt

build: configure
	cmake --build $(BUILD_DIR)

run: build
	"$(BUILD_DIR)/$(NAME)$(EXE)"

# Optimized build in a separate folder so it doesn't disturb the Debug one
$(RELEASE_DIR)/CMakeCache.txt:
	cmake -S . -B $(RELEASE_DIR) -G "$(GENERATOR)" -DCMAKE_BUILD_TYPE=Release

release: $(RELEASE_DIR)/CMakeCache.txt
	cmake --build $(RELEASE_DIR)

run-release: release
	"$(RELEASE_DIR)/$(NAME)$(EXE)"

clean:
	cmake -E rm -rf $(BUILD_DIR) $(RELEASE_DIR)

rebuild: clean build
