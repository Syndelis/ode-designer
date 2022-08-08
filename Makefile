CC=g++ -std=c++17
CFLAGS=-g -Wno-unused-result -ffunction-sections -fdata-sections -ffast-math -Wl,--gc-sections -Wl,--print-gc-sections
CFLAGS_LIB=-c

IMGUI_SRC=$(wildcard lib/imgui/imgui*.cpp) lib/imgui/backends/imgui_impl_glfw.cpp lib/imgui/backends/imgui_impl_opengl3.cpp lib/imnodes/imnodes.cpp
IMGUI_SRC_PATH=$(sort $(foreach src,$(IMGUI_SRC),$(dir $(src))))

GLFW_SRC=lib/glfw
GLFW_BUILD_DIR=$(GLFW_SRC)/build
GLFW_LIB=$(GLFW_BUILD_DIR)/src/libglfw3.a

INCLUDE_DIRS=-I. $(foreach path,$(IMGUI_SRC_PATH),-I$(path)) -I$(GLFW_SRC)/include
LINK_DIRS=
LINKS=-lGL -lm -ldl -pthread
DEFINE=

OBJ_DIR=obj
SRC=$(wildcard src/**/*.cpp) $(IMGUI_SRC)
OBJ=$(foreach src,$(SRC),$(OBJ_DIR)/$(notdir $(basename $(src))).o)
EXE=main

VPATH=$(wildcard src/*) $(IMGUI_SRC_PATH) $(dir GLFW_LIB)

all: $(GLFW_LIB) app
app: $(OBJ_DIR) $(EXE)

$(GLFW_LIB):
	mkdir -p $(GLFW_BUILD_DIR)
	cmake -S $(GLFW_SRC) -B $(GLFW_BUILD_DIR)
	make -C $(GLFW_BUILD_DIR)

$(OBJ_DIR):
	mkdir -p $@

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(GLFW_LIB) -o $@ $(INCLUDE_DIRS) $(LINK_DIRS) $(LINKS) $(DEFINE)

$(OBJ): $(OBJ_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $(CFLAGS_LIB) $< -o $@ $(INCLUDE_DIRS) $(LINK_DIRS) $(LINKS) $(DEFINE)

clean: app/clean
	rm -rf $(GLFW_BUILD_DIR) $(OBJ_DIR) $(EXE)

app/clean:
	rm -rf $(OBJ_DIR) $(EXE)