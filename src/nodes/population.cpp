#include "population.hpp"

#include <algorithm>
#include <imnodes.h>
#include <odeir.hpp>

#include "../nodes/node.hpp"

#include "../pins/echo.hpp"
#include "../pins/name_echoer.hpp"
#include "../pins/sign.hpp"

Population::Population(char *name) : Node(name) {
    name_echoer = pushOutput<NameEchoerPin>();
    pushInput<SignPin>();
}

void Population::renderContent() {
    float value;

    ImGui::PushItemWidth(100);
    ImGui::InputFloat("", &value);
       
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

Model Population::serializeInto(Model model) {

    auto popState = model.buildNode(id, name).withRelatedConstant("TODO!");

    if (name_echoer->linkedTo.empty())
        return popState;

    std::vector<ElementID> keys;

    for (auto &[id, pin] : name_echoer->linkedTo)
        keys.push_back(id);

    // TODO: Sign
    auto linkState = popState.addLink(keys[0], '+');

    for (int i = 1; i < keys.size(); i++)
        linkState = linkState.addLink(keys[i], '+');

    return linkState;
}
