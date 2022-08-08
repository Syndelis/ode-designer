#include "population.h"
#include "../pins/echo.h"
#include "../pins/ghost.h"
#include "../nodes/node.h"
#include <imnodes.h>
#include <algorithm>

Population::Population(char *name) : Node(name) {
    pushInput<EchoPin>();
    ghost = pushOutput<GhostPin>();
}

Population::~Population() {}

void Population::renderContent() {}

bool Population::onPinLinked(Pin *thisPin, Node *otherNode) {
    pushInput<EchoPin>();
    return true;
}

void Population::onPinUnlinked(Pin *thisPin, Node *otherNode) {
    inputs.erase(std::find(inputs.begin(), inputs.end(), thisPin));
}