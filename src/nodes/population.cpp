#include "population.h"
#include "../pins/echo.h"
#include "../pins/sign.h"
#include "../pins/name_echoer.h"
#include "../nodes/node.h"
#include "imgui.h"
#include <imnodes.h>
#include <algorithm>

Population::Population(char *name) : Node(name), value(0) {
    name_echoer = pushOutput<NameEchoerPin>();
    pushInput<SignPin>();
}

Population::~Population() {}

void Population::renderContent() {
    ImGui::InputFloat("##Scale", &value);
}

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
