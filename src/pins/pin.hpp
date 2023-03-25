#ifndef PINS_PIN_H
#define PINS_PIN_H

#include <map>
#include <variant>
#include <imnodes.h>
#include "../core/element.hpp"
#include "../nodes/node.hpp"
#include "../common/pin_type.hpp"
#include <iostream>
#include <stdio.h>

enum class PinShape : char {
    Circle=ImNodesPinShape_CircleFilled,
    Square=ImNodesPinShape_QuadFilled,
    Triangle=ImNodesPinShape_TriangleFilled,
};

void pushShapeStyle(PinShape shape);
void popShapeStyle(PinShape shape);

class Pin;

typedef struct {
    Pin *target;
    bool isVisible;
} LinkedPin;

class Node;
class Pin : public Element {
public:
    inline static std::map<ElementID, Pin*> allPins;
    std::map<ElementID, LinkedPin> linkedTo;
    PinType type;
    PinShape shape;
    Node *parent;
    bool canLink;
    std::variant<bool, int, float, std::string> data;

    static void unlink(ElementID linkId);
    static void linkTogether(ElementID linkId1, ElementID linkId2, bool isVisible=true);
    
    Pin(PinType type, Node *parent);
    ~Pin() override;
    void link(Pin *other, bool isVisible=true);
    void renderLinks();

    template<typename T> void setData(T data) {
        this->data = data;
        for (auto &[_, linkedPin] : linkedTo) {
            Pin *pin = linkedPin.target;
            pin->trySendData(data);
        }
    }

    template<typename T> const T *getData() {
        return std::get_if<T>(&this->data);
    }

    virtual bool acceptsData() { return false; }

    template<typename T> inline void trySendData(T data) {
        if (acceptsData()) setData(data);
    }

    virtual void renderPinConnector();
};

#endif