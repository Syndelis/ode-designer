#include "population.hpp"

#include <algorithm>
#include <imnodes.h>

#include "../nodes/node.hpp"

#include "../pins/echo.hpp"
#include "../pins/name_echoer.hpp"
#include "../pins/sign.hpp"

Population::Population(char *name) : Node(name), value(0) {
    if (allPopulations.contains(this->name)) {
        throw new PopulationExistsException(this->name.c_str());
    }
    allPopulations[this->name] = this;
    name_echoer                = pushOutput<NameEchoerPin>();
    pushInput<SignPin>();
}

Population::~Population() { allPopulations.erase(this->name); }

Population *Population::getByName(const std::string &name) {
    if (allPopulations.contains(name)) {
        return allPopulations[name];
    }
    return nullptr;
}

void Population::renderContent() { ImGui::InputFloat("##Scale", &value); }

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
