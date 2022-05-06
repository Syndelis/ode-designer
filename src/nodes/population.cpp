#include "population.h"
#include "../pins/numeric.h"
#include <imnodes.h>

Population::Population(char *name) : Node(name) {
    outputs.push_back(new NumericPin());
}

Population::~Population() {}

void Population::renderContent() {}