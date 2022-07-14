#include "population.h"
#include "../pins/echo.h"
#include <imnodes.h>

Population::Population(char *name) : Node(name) {
    pushInput<EchoPin>();
}

Population::~Population() {}

void Population::renderContent() {}