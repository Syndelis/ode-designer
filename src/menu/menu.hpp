#ifndef MENU_HPP
#define MENU_HPP

#include "../nodes/combinator.hpp"
#include "../nodes/node.hpp"
#include "../nodes/population.hpp"
#include "../plot/plot.hpp"
#include "portable-file-dialogs.h"
#include "../simulation/interactive_simulation.h"

static bool isContextMenuOpen = false;
// Context Menu --------------------------------------------
using NodeFactory = Node *(*)(char *);

#define NODE_ENTRY(name)          \
    {                             \
#name, createNode < name> \
    }
const int MAX_NODE_NAME_LENGTH = 50;

template <typename T>

Node *createNode(char *name) {
    return new T(name); // NOLINT(cppcoreguidelines-owning-memory)
}

static std::map<std::string, NodeFactory> nodeFactories = {
    NODE_ENTRY(Population),
    NODE_ENTRY(Combinator),
};

static NodeFactory *currentFactory         = nullptr;
static std::string currentNodeName         = "";
static char nodeName[MAX_NODE_NAME_LENGTH] = "";

void resetContextMenuState();// Reset context menu state

void openContextMenu();// Open context menu

void renderContextMenu();// Render context menu

void menuBarFile();// Menu bar file

void menuBarEdit();// Menu bar edit

void menuOpenfile();// Menu open file

void menuSavefile();// Menu save file

//void menuSavefileAs();// Menu save file as 

#endif // MENU_HPP