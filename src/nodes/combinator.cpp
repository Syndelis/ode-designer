#include "combinator.hpp"
#include "../pins/pin.hpp"
#include "../pins/echo.hpp"
#include "../pins/ghost.hpp"
#include "../common/imgui_combo.hpp"
#include <imgui.h>
#include <algorithm>
#include <thread>

#define FMT_HEADER_ONLY
#include <fmt/std.h>

static const char *options[] = {"*", "/", "+", "-"};

void updateExpression(Combinator *comb) {

    std::string expression = "(";
    const char *operation = options[comb->selected]; // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)

    for (Pin *pin : comb->inputs)
        if (pin->data.index()) // This line guarantees only initialized objects are used
            expression.append(
                fmt::format("{}{}", pin->data, operation)
            );

    if (expression.length() > 0) {
        expression.pop_back();
        expression.push_back(')');
    }

    comb->expression_pin->setData(expression);

}

void Combinator::updateExpressionInBackground() {
    std::thread{updateExpression, this}.detach();
}

Combinator::Combinator(char *name) : Node(name), selected(0) {
    expression_pin = pushOutput<EchoPin>();
    pushInput<EchoPin>();
}

void Combinator::renderContent() {

    int prevSelected = selected;

    ImGui::Text("Opeartion: ");
    ImGui::SameLine();
    IMGUI_COMBO("##operationcombo", options, selected, 0);  // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)

    if (prevSelected != selected)
        updateExpressionInBackground();

}

bool Combinator::onPinLinked(Pin *thisPin, Node *otherNode) {

    if (!Node::onPinLinked(thisPin, otherNode))
        return false;

    if (thisPin->type == PinType::Input) {
        pushInput<EchoPin>();

        // If the other pin's parent is a Combinator, then we shouldn't
        // try to make automatic links, since that would bring us to a loop.
        // After all, the other Combinator doesn't need our expression, it
        // is responsible for supplying it to us!
        if (!dynamic_cast<Combinator*>(otherNode)) {
            Pin *otherPin = otherNode->getNextAvailablePin(PinType::Input);  // NOLINT(clang-analyzer-core.CallAndMessage)
            Pin::linkTogether(expression_pin->id, otherPin->id, false);
        }

        updateExpressionInBackground();
    }

    return true;

}

void Combinator::onPinUnlinked(Pin *thisPin, Node *otherNode) {

    if (thisPin->type == PinType::Input) {

        ElementID linkId = 0;
        for (auto &[thisLinkId, linkedPin] : expression_pin->linkedTo)
            if (linkedPin.target->parent == otherNode)
                linkId = thisLinkId;

        Pin::unlink(linkId);
        inputs.erase(std::find(inputs.begin(), inputs.end(), thisPin));

        updateExpressionInBackground();
    
    }

}