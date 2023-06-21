CPP_STD=-std=c++20
CC=g++ $(CPP_STD)
CFLAGS=-g
CFLAGS_LIB=-c

release : CFLAGS=-g -Wno-unused-result -ffunction-sections -fdata-sections -ffast-math -Wl,--gc-sections -Wl,--print-gc-sections

IMGUI_SRC=$(wildcard lib/imgui/imgui*.cpp) lib/imgui/backends/imgui_impl_glfw.cpp lib/imgui/backends/imgui_impl_opengl3.cpp lib/imnodes/imnodes.cpp
IMGUI_SRC_PATH=$(sort $(foreach src,$(IMGUI_SRC),$(dir $(src))))

GLFW_SRC=lib/glfw
GLFW_BUILD_DIR=$(GLFW_SRC)/build
GLFW_LIB=$(GLFW_BUILD_DIR)/src/libglfw3.a

FMT_INC=lib/fmt/include

ODEIR_PATH=lib/odeir
ODEIR_INC=$(ODEIR_PATH)/include
ODEIR_LIB=$(ODEIR_PATH)/target/debug/libodeir.a
ODEIR_MANIFEST_FILE=$(ODEIR_PATH)/Cargo.toml

ODEIR_CPP_PATH=$(ODEIR_PATH)/cpp-src
ODEIR_CPP_SRC=$(wildcard $(ODEIR_CPP_PATH)/**.cpp)

INCLUDE_DIRS=-I. $(foreach path,$(IMGUI_SRC_PATH),-I$(path)) -I$(GLFW_SRC)/include -I$(FMT_INC) -I$(ODEIR_INC)
LINK_DIRS=
LINKS=-lGL -lm -ldl -pthread
DEFINE=

OBJ_DIR=obj

SRC=$(wildcard src/**/*.cpp)
HEADERS=$(wildcard src/**/*.h*)

SRC_OBJ=$(foreach src,$(SRC),$(OBJ_DIR)/$(notdir $(basename $(src))).o)
IMGUI_OBJ=$(foreach src,$(IMGUI_SRC),$(OBJ_DIR)/$(notdir $(basename $(src))).o)
# ODEIR_CPP_OBJ=$(foreach src,$(ODEIR_CPP_SRC),$(OBJ_DIR)/$(notdir $(basename $(src))).o)
ODEIR_CPP_OBJ=
OBJ=$(SRC_OBJ) $(IMGUI_OBJ) $(ODEIR_CPP_OBJ)

EXE=main

VPATH=$(wildcard src/*) $(IMGUI_SRC_PATH) $(ODEIR_CPP_PATH) $(dir GLFW_LIB)

all: $(GLFW_LIB) $(EXE)
release: all

$(GLFW_LIB):
	mkdir -p $(GLFW_BUILD_DIR)
	cmake -S $(GLFW_SRC) -B $(GLFW_BUILD_DIR)
	make -C $(GLFW_BUILD_DIR)

$(OBJ_DIR):
	mkdir -p $@

$(EXE): $(OBJ_DIR) $(OBJ) $(ODEIR_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(ODEIR_LIB) $(GLFW_LIB) -o $@ $(INCLUDE_DIRS) $(LINK_DIRS) $(LINKS) $(DEFINE)

$(OBJ): $(OBJ_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $(CFLAGS_LIB) $< -o $@ $(INCLUDE_DIRS) $(LINK_DIRS) $(LINKS) $(DEFINE)

$(ODEIR_LIB):
	cargo build --manifest-path $(ODEIR_MANIFEST_FILE)

full-clean: clean
	rm -rf $(OBJ_DIR) $(GLFW_BUILD_DIR)
	cargo clean --manifest-path $(ODEIR_MANIFEST_FILE)

clean:
	rm -f $(SRC_OBJ) $(EXE)

lint:
	clang-tidy $(SRC) $(HEADERS) -- $(CPP_STD) $(INCLUDE_DIRS) $(LINK_DIRS) $(LINKS) $(DEFINE)

format:
	clang-format -i $(SRC) $(HEADERS)

check-format:
	clang-format -i $(SRC) $(HEADERS) --dry-run -Werror

enable-git-hooks:
	git config --local include.path ./.gitconfig
