CC=g++ -std=c++17
CFLAGS=-g -Wno-unused-result -ffunction-sections -fdata-sections -ffast-math -Wl,--gc-sections -Wl,--print-gc-sections
CFLAGS_LIB=-c

IMGUI_SRC=$(wildcard lib/imgui/imgui*.cpp) lib/imgui/backends/imgui_impl_glfw.cpp lib/imgui/backends/imgui_impl_opengl3.cpp lib/imnodes/imnodes.cpp
IMGUI_SRC_PATH=$(sort $(foreach src,$(IMGUI_SRC),$(dir $(src))))

INCLUDE_DIRS=-I. $(foreach path,$(IMGUI_SRC_PATH),-I$(path))
LINK_DIRS=
LINKS=-lglfw -lGL -lm -ldl
DEFINE=

OBJ_DIR=obj
SRC=$(wildcard src/**/*.cpp) $(IMGUI_SRC)
OBJ=$(foreach src,$(SRC),$(OBJ_DIR)/$(notdir $(basename $(src))).o)
EXE=main

VPATH=$(wildcard src/*) $(IMGUI_SRC_PATH)

all: $(OBJ_DIR) $(EXE)

$(OBJ_DIR):
	mkdir -p $@

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(INCLUDE_DIRS) $(LINK_DIRS) $(LINKS) $(DEFINE)

$(OBJ): $(OBJ_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $(CFLAGS_LIB) $< -o $@ $(INCLUDE_DIRS) $(LINK_DIRS) $(LINKS) $(DEFINE)

clean:
	rm -rf $(OBJ_DIR) $(EXE)
