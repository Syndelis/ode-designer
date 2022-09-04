#include "combinator.h"
#include "../pins/pin.h"
#include "../pins/echo.h"
#include "../pins/ghost.h"
#include "../common/imgui_combo.h"
#include <imgui.h>
#include <algorithm>
#include <thread>

#define FMT_HEADER_ONLY
#include <fmt/std.h>

static const char *options[] = {"*", "/"};

void updateExpression(Combinator *comb) {

    std::string expression = "";
    const char *operation = options[comb->selected];

    for (Pin *pin : comb->inputs)
        if (pin->data.index())
            expression\
                .append(fmt::format("{}", pin->data))\
                .append(operation);

    if (expression.length() > 0)
        expression.pop_back();

    comb->expression_pin->setData(expression);

}

Combinator::Combinator(char *name) : Node(name), selected(0) {
    expression_pin = pushOutput<EchoPin>();
    pushInput<EchoPin>();
}

Combinator::~Combinator() {}

void Combinator::renderContent() {

    ImGui::Text("Opeartion: ");
    ImGui::SameLine();
    IMGUI_COMBO("##operationcombo", options, selected, 0);

}

bool Combinator::onPinLinked(Pin *thisPin, Node *otherNode) {

    if (thisPin->type == PinType::Input) {
        pushInput<EchoPin>();

        std::string expression = "";
        const char *operation = options[selected];


        Pin *otherPin = otherNode->getNextAvailablePin(PinType::Input);
        Pin::linkTogether(expression_pin->id, otherPin->id);

        std::thread{updateExpression, this}.detach();
    }

    return true;

}

void Combinator::onPinUnlinked(Pin *thisPin, Node *otherNode) {

    if (thisPin->type == PinType::Input) {

        int linkId = 0;
        for (auto &[thisLinkId, pin] : expression_pin->linkedTo)
            if (pin->parent == otherNode)
                linkId = thisLinkId;

        Pin::unlink(linkId);
        inputs.erase(std::find(inputs.begin(), inputs.end(), thisPin));
    
    }

}