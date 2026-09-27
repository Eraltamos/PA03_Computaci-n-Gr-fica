#include "Light.hpp"

Light::Light() : pointLightEnabled(true) {
    // Luz 0 direccional cenital 
    dirPosition[0] = 0.0f; dirPosition[1] = 1.0f; dirPosition[2] = 0.5f; dirPosition[3] = 0.0f;
    dirAmbient[0] = 0.15f; dirAmbient[1] = 0.18f; dirAmbient[2] = 0.22f; dirAmbient[3] = 1.0f;
    dirDiffuse[0] = 0.45f; dirDiffuse[1] = 0.50f; dirDiffuse[2] = 0.55f; dirDiffuse[3] = 1.0f;
    dirSpecular[0] = 0.30f; dirSpecular[1] = 0.30f; dirSpecular[2] = 0.35f; dirSpecular[3] = 1.0f;

    // Luz 1 Puntual local con la lampara
    pointPosition[0] = 2.8f; pointPosition[1] = 3.2f; pointPosition[2] = 2.4f; pointPosition[3] = 1.0f;
    pointAmbient[0] = 0.05f; pointAmbient[1] = 0.04f; pointAmbient[2] = 0.02f; pointAmbient[3] = 1.0f;
    pointDiffuse[0] = 1.0f;  pointDiffuse[1] = 0.85f; pointDiffuse[2] = 0.55f; pointDiffuse[3] = 1.0f;
    pointSpecular[0] = 1.0f; pointSpecular[1] = 0.95f; pointSpecular[2] = 0.80f; pointSpecular[3] = 1.0f;
}

void Light::init() {
    glEnable(GL_LIGHTING);

    // Configuracion de Luz 0
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, dirAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dirDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, dirSpecular);

    // Configuracion de Luz 1 con atenuacion radial
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, pointAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, pointDiffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, pointSpecular);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.05f);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.02f);
}

void Light::apply() {
    // Se aplican las coordenadas en el espacio del modelo
    glLightfv(GL_LIGHT0, GL_POSITION, dirPosition);

    if (pointLightEnabled) {
        glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1, GL_POSITION, pointPosition);
    } else {
        glDisable(GL_LIGHT1);
    }
}

void Light::togglePointLight() {
    pointLightEnabled = !pointLightEnabled;
}

void Light::movePointLightX(float delta) {
    pointPosition[0] += delta;
    if (pointPosition[0] > 6.0f) pointPosition[0] = 6.0f;
    if (pointPosition[0] < -6.0f) pointPosition[0] = -6.0f;
}