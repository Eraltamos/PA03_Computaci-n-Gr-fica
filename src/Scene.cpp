#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include "Scene.hpp"

#if defined(__APPLE__)
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

Scene::Scene()
    : orbRotation(0.0f), orbLevitation(2.65f), timeAccumulator(0.0f),
      textureEnabled(true), smoothShading(true), depthTestEnabled(true),
      orbMaterialMode(0) {}

void Scene::init() {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);

    lightSystem.init();

    // Carga de textura
    celestialTexture.loadBMP("assets/textures/mapa_estelar.bmp");
}

void Scene::update(float deltaTime) {
    timeAccumulator += deltaTime;

    // Rotacion polar continua y levitacion armonica sinusoidal
    orbRotation += 45.0f * deltaTime;
    if (orbRotation >= 360.0f) orbRotation -= 360.0f;

    orbLevitation = 2.65f + 0.20f * std::sin(timeAccumulator * 2.5f);
}

void Scene::toggleShading() {
    smoothShading = !smoothShading;
    glShadeModel(smoothShading ? GL_SMOOTH : GL_FLAT);
    std::cout << "[Sombreado] Modelo: " << (smoothShading ? "SMOOTH (Gouraud/Phong)" : "FLAT (Facetado)") << std::endl;
}

void Scene::cycleOrbMaterial() {
    orbMaterialMode = (orbMaterialMode + 1) % 3;
    switch (orbMaterialMode) {
        case 0: std::cout << "[Material Orbe] Oro Metalico Especular" << std::endl; break;
        case 1: std::cout << "[Material Orbe] Plastico Rubi Difuso" << std::endl; break;
        case 2: std::cout << "[Material Orbe] Jade Opaco Mate" << std::endl; break;
    }
}

// Suelo del observatorio
void Scene::drawFloor() {
    Material::floorStone().apply();
    glPushMatrix();
        glTranslatef(0.0f, -0.05f, 0.0f);
        Model::drawBox(16.0f, 0.1f, 16.0f);
    glPopMatrix();
}

// Pedestal central octogonal
void Scene::drawPedestal() {
    Material::pedestalMarble().apply();
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.0f);
        Model::drawCylinder(1.2f, 1.0f, 0.4f, 8);
        glTranslatef(0.0f, 0.4f, 0.0f);
        Model::drawCylinder(1.0f, 0.85f, 1.0f, 8);
        glTranslatef(0.0f, 1.0f, 0.0f);
        Model::drawCylinder(0.95f, 0.95f, 0.15f, 8);
    glPopMatrix();
}

// Orbe o planeta levitante
void Scene::drawOrb() {
    switch (orbMaterialMode) {
        case 0: Material::metallicGold().apply(); break;
        case 1: Material::rubyPlastic().apply(); break;
        case 2: Material::matteJade().apply(); break;
    }

    glPushMatrix();
        glTranslatef(0.0f, orbLevitation, 0.0f);
        glRotatef(orbRotation, 0.0f, 1.0f, 0.0f);
        glRotatef(23.5f, 0.0f, 0.0f, 1.0f); // Inclinacion axial
        Model::drawSphere(0.65f, 32, 24);

        // Anillo de suspension exterior
        Material::brassLamp().apply();
        Model::drawCylinder(0.85f, 0.85f, 0.04f, 24);
    glPopMatrix();
}

// Consola astronomica de monitoreo
void Scene::drawAstralConsole() {
    Material::darkConsole().apply();
    glPushMatrix();
        glTranslatef(-2.8f, 0.0f, 0.5f);
        glRotatef(35.0f, 0.0f, 1.0f, 0.0f);

        glTranslatef(0.0f, 0.6f, 0.0f);
        Model::drawBox(1.2f, 1.2f, 0.9f);

        glTranslatef(0.0f, 0.65f, -0.05f);
        glRotatef(-25.0f, 1.0f, 0.0f, 0.0f);
        Model::drawBox(1.1f, 0.12f, 0.7f);
    glPopMatrix();
}

// Lampara de pie emisora o Luz 1
void Scene::drawStandingLamp() {
    Material::brassLamp().apply();
    const GLfloat* pos = lightSystem.getPointPosition();

    glPushMatrix();
        glTranslatef(pos[0], 0.0f, pos[2]);

        // Base y poste vertical
        Model::drawCylinder(0.35f, 0.30f, 0.1f, 16);
        Model::drawCylinder(0.06f, 0.06f, pos[1], 12);

        // Foco emisor
        glTranslatef(0.0f, pos[1], 0.0f);
        Model::drawCylinder(0.25f, 0.10f, 0.35f, 16);

        // Indicador visual de la bombilla con componente emisiva si esta encendida
        if (lightSystem.isPointLightEnabled()) {
            GLfloat bulbEmission[] = { 1.0f, 0.9f, 0.6f, 1.0f };
            glMaterialfv(GL_FRONT, GL_EMISSION, bulbEmission);
            Model::drawSphere(0.12f, 16, 12);
            GLfloat noEmission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
            glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);
        }
    glPopMatrix();
}

// Panel mural de calibracion estelar que Soporta Texturizado
void Scene::drawCalibrationWall() {
    Material::wallPanel().apply();
    glPushMatrix();
        glTranslatef(0.0f, 2.5f, -4.8f);

        if (textureEnabled && celestialTexture.getIsLoaded()) {
            glEnable(GL_TEXTURE_2D);
            celestialTexture.bind();
        }

        // Lienzo mural vertical
        Model::drawTexturedQuad(5.5f, 3.5f);

        if (textureEnabled && celestialTexture.getIsLoaded()) {
            celestialTexture.unbind();
            glDisable(GL_TEXTURE_2D);
        }

        // Marco arquitectonico perimetral
        Material::pedestalMarble().apply();
        glTranslatef(0.0f, 0.0f, -0.05f);
        Model::drawBox(5.7f, 3.7f, 0.08f);
    glPopMatrix();
}

void Scene::render(const Camera& camera) {
    if (depthTestEnabled) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }

    glClearColor(0.04f, 0.05f, 0.08f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera.applyView();
    lightSystem.apply();

    drawFloor();
    drawPedestal();
    drawOrb();
    drawAstralConsole();
    drawStandingLamp();
    drawCalibrationWall();

    glutSwapBuffers();
}