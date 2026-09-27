#ifndef SCENE_HPP
#define SCENE_HPP

#include "Camera.hpp"
#include "Light.hpp"
#include "Material.hpp"
#include "Model.hpp"
#include "Texture.hpp"

class Scene {
private:
    Light lightSystem;
    Texture celestialTexture;

    // Estados de animación
    float orbRotation;
    float orbLevitation;
    float timeAccumulator;

    // Estados de experimentación interactiva
    bool textureEnabled;
    bool smoothShading;
    bool depthTestEnabled;
    int orbMaterialMode; // 0: Oro, 1: rojo, 2: verde

    // Subrutinas
    void drawFloor();
    void drawPedestal();
    void drawOrb();
    void drawAstralConsole();
    void drawStandingLamp();
    void drawCalibrationWall();

public:
    Scene();

    void init();
    void update(float deltaTime);
    void render(const Camera& camera);

    // Controles
    void toggleTexture() { textureEnabled = !textureEnabled; }
    void toggleShading();
    void toggleDepthTest() { depthTestEnabled = !depthTestEnabled; }
    void cycleOrbMaterial();
    Light& getLight() { return lightSystem; }
};

#endif // SCENE_HPP