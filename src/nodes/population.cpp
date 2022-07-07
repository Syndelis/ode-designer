#include "population.h"
#include "../pins/numeric.h"
#include <imnodes.h>

Population::Population(char *name) : Node(name) {
    inputs.push_back(new NumericPin(PinType::Input));
}

Population::~Population() {}

void Population::renderContent() {}