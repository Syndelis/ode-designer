#include "pin.hpp"

#include <cstdio>
#include <imnodes.h>
#include <iostream>
#include <map>

#include "../common/pin_type.hpp"
#include "../core/element.hpp"

#include "../nodes/node.hpp"

void Pin::unlink(ElementID linkId) {
    for (auto &[id, pin] : allPins)
        if (pin->linkedTo.count(linkId)) {
            Pin *otherPin     = pin->linkedTo.extract(linkId).mapped().target;
            otherPin->canLink = true;

            Node *parent      = pin->parent;
            Node *otherParent = otherPin->parent;

            parent->onPinUnlinked(pin, otherParent);
            otherParent->onPinUnlinked(otherPin, parent);

            break;
        }
}

void Pin::linkTogether(ElementID linkId1, ElementID linkId2, bool isVisible) {
    Pin *pin1 = allPins[linkId1];
    Pin *pin2 = allPins[linkId2];

    Node *parent1 = pin1->parent;
    Node *parent2 = pin2->parent;

    bool canLink = true;

    canLink &= parent1->onPinLinked(pin1, parent2);
    canLink &= parent2->onPinLinked(pin2, parent1);

    if (!canLink)
        return;

    switch (pin1->type) {
        case PinType::Input:
            pin2->link(pin1, isVisible);
            break;

        case PinType::Output:
            pin1->link(pin2, isVisible);
            break;
    }
}

Pin::Pin(PinType type, Node *parent)
    : Element(), type(type), parent(parent), canLink(true) {
    allPins[id] = this;
    shape       = PinShape::Circle;
    data        = false;
}

Pin::~Pin() { allPins.erase(id); }

void Pin::link(Pin *other, bool isVisible) {
    linkedTo[getNextId()]
        = LinkedPin { .target = other, .isVisible = isVisible };
    other->canLink = false;

    if (data.index())
        other->trySendData(data);
}

void Pin::renderLinks() {
    for (auto &[linkId, dstLinkedPin] : linkedTo) {
        Pin *dstPin    = dstLinkedPin.target;
        bool isVisible = dstLinkedPin.isVisible;

        if (isVisible)
            ImNodes::Link(linkId, id, dstPin->id);
    }
}

void pushShapeStyle(PinShape shape) {
    switch (shape) {
        case PinShape::Circle:
            ImNodes::PushColorStyle(ImNodesCol_Pin, 0xFFAA6423);
            break;

        case PinShape::Square:
            ImNodes::PushColorStyle(ImNodesCol_Pin, 0xFF4E25ED);
            break;

        case PinShape::Triangle:
            ImNodes::PushColorStyle(ImNodesCol_Pin, 0xFF8B991B);
            break;
    }
}

void popShapeStyle(PinShape shape) { ImNodes::PopColorStyle(); }

void Pin::renderPinConnector() {
    pushShapeStyle(shape);

    switch (type) {
        case PinType::Input:
            ImNodes::BeginInputAttribute(id, (ImNodesPinShape)shape ^ canLink);
            break;
        case PinType::Output:
            ImNodes::BeginOutputAttribute(id, (ImNodesPinShape)shape);
            break;
    }

    renderContent();

    switch (type) {
        case PinType::Input:
            ImNodes::EndInputAttribute();
            break;
        case PinType::Output:
            ImNodes::EndOutputAttribute();
            break;
    }

    popShapeStyle(shape);
}
