#include "population.hpp"

#include <algorithm>
#include <imnodes.h>

#include "../nodes/node.hpp"

#include "../pins/echo.hpp"
#include "../pins/name_echoer.hpp"
#include "../pins/sign.hpp"

Population::Population(char *name) : Node(name) {
    name_echoer = pushOutput<NameEchoerPin>();
    pushInput<SignPin>();
}

void Population::renderContent() {}

bool Population::onPinLinked(Pin *thisPin, Node *otherNode) {

    if (!Node::onPinLinked(thisPin, otherNode))
        return false;

    if (thisPin->type == PinType::Input)
        pushInput<SignPin>();

    return true;
}

void Population::onPinUnlinked(Pin *thisPin, Node *otherNode) {

    if (thisPin->type == PinType::Input)
        inputs.erase(std::find(inputs.begin(), inputs.end(), thisPin));
}