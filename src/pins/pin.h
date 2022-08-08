#ifndef PINS_PIN_H
#define PINS_PIN_H

#include <map>
#include <imnodes.h>
#include "../core/element.h"
#include "../nodes/node.h"
#include "../common/pin_type.h"
#include <iostream>
#include <stdio.h>

enum class PinShape : char {
    Circle=ImNodesPinShape_CircleFilled,
    Square=ImNodesPinShape_QuadFilled,
    Triangle=ImNodesPinShape_TriangleFilled,
};

void pushShapeStyle(PinShape shape);
void popShapeStyle(PinShape shape);

class Node;
class Pin : public Element {
public:
    inline static std::map<unsigned int, Pin*> allPins;
    std::map<int, Pin*> linkedTo;
    PinType type;
    PinShape shape;
    Node *parent;

    static void unlink(int linkId);
    static void linkTogether(int linkId1, int linkId2);
    
    Pin(PinType type, Node *parent);
    virtual ~Pin();
    void link(Pin *other);
    void renderLinks();

    virtual void renderPinConnector();
};

#endif