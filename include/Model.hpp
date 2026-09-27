#ifndef MODEL_HPP
#define MODEL_HPP

class Model {
public:
    static void drawBox(float sx, float sy, float sz);
    static void drawCylinder(float baseRadius, float topRadius, float height, int slices);
    static void drawSphere(float radius, int slices, int stacks);
    static void drawTexturedQuad(float width, float height);
};

#endif // MODEL_HPP