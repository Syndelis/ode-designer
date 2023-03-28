#include "combinator.hpp"

#include <algorithm>
#include <imgui.h>
#include <thread>

#include "../common/imgui_combo.hpp"

#include "../pins/echo.hpp"
#include "../pins/ghost.hpp"
#include "../pins/pin.hpp"

#define FMT_HEADER_ONLY
#include <fmt/std.h>

static const char *options[] = { "*", "/", "+", "-" };

void updateExpression(Combinator *comb) {

    std::string expression = "(";

    // SAFETY: `selected` is populated solely via ImGui using `options` as the
    // source of truth. Therefore, it is guaranteed to be within its bounds.
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
    const char *operation = options[comb->selected];

    for (Pin *pin : comb->inputs) {
        if (pin->data.index())
            expression.append(fmt::format("{}{}", pin->data, operation));

    if (expression.length() > 0) {
        expression.pop_back();
        expression.push_back(')');
    }

    comb->expression_pin->setData(expression);
}

void Combinator::updateExpressionInBackground() {
    std::thread { updateExpression, this }.detach();
}

Combinator::Combinator(char *name) : Node(name), selected(0) {
    expression_pin = pushOutput<EchoPin>();
    pushInput<EchoPin>();
}

void Combinator::renderContent() {

    int prevSelected = selected;

    ImGui::Text("Opeartion: ");
    ImGui::SameLine();

    // SAFETY: Read previous comment.
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
    IMGUI_COMBO("##operationcombo", options, selected, 0);

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
        if (!dynamic_cast<Combinator *>(otherNode)) {
            // SAFETY: `otherNode` is guaranteed to always be non-null.
            // TODO: Use reference instead of pointer.
            // NOLINTNEXTLINE(clang-analyzer-core.CallAndMessage)
            Pin *otherPin = otherNode->getNextAvailablePin(PinType::Input);
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
