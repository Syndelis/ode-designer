#include "assigner.hpp"
#include "src/pins/echo.hpp"
#include "src/pins/sign.hpp"
#include "population.hpp"


Assigner::Assigner(char* name): Node(name) {
    auto node = Population::getByName(name);
    if (node == nullptr) {
        throw new PopulationNotFoundException(this->name);
    }
    pushInput<EchoPin>();
}

void Assigner::renderContent() {
     
}

bool Assigner::onPinLinked(Pin *thisPin, Node *otherNode) {
    if (!Node::onPinLinked(thisPin, otherNode)) {
        return false;
    }
    if (thisPin->type == PinType::Output) {
        return false;
    }

    return true;
}

void Assigner::onPinUnlinked(Pin *thisPin, Node *otherNode) {

}
