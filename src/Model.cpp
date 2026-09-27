#define _USE_MATH_DEFINES
#include <cmath>
#include "Model.hpp"

#if defined(__APPLE__)
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

void Model::drawBox(float sx, float sy, float sz) {
    float x = sx * 0.5f;
    float y = sy * 0.5f;
    float z = sz * 0.5f;

    glBegin(GL_QUADS);
    // Cara Frontal (+Z)
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-x, -y,  z); glVertex3f( x, -y,  z);
    glVertex3f( x,  y,  z); glVertex3f(-x,  y,  z);
    // Cara Trasera (-Z)
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-x, -y, -z); glVertex3f(-x,  y, -z);
    glVertex3f( x,  y, -z); glVertex3f( x, -y, -z);
    // Cara Superior (+Y)
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-x,  y, -z); glVertex3f(-x,  y,  z);
    glVertex3f( x,  y,  z); glVertex3f( x,  y, -z);
    // Cara Inferior (-Y)
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-x, -y, -z); glVertex3f( x, -y, -z);
    glVertex3f( x, -y,  z); glVertex3f(-x, -y,  z);
    // Cara Derecha (+X)
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f( x, -y, -z); glVertex3f( x,  y, -z);
    glVertex3f( x,  y,  z); glVertex3f( x, -y,  z);
    // Cara Izquierda (-X)
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-x, -y, -z); glVertex3f(-x, -y,  z);
    glVertex3f(-x,  y,  z); glVertex3f(-x,  y, -z);
    glEnd();
}

void Model::drawCylinder(float baseRad, float topRad, float height, int slices) {
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= slices; ++i) {
        float angle = static_cast<float>(i) * 2.0f * static_cast<float>(M_PI) / static_cast<float>(slices);
        float cosA = std::cos(angle);
        float sinA = std::sin(angle);

        glNormal3f(cosA, 0.0f, sinA);
        glVertex3f(baseRad * cosA, 0.0f, baseRad * sinA);
        glVertex3f(topRad * cosA, height, topRad * sinA);
    }
    glEnd();

    // Tapa superior
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    for (int i = 0; i < slices; ++i) {
        float angle = static_cast<float>(i) * 2.0f * static_cast<float>(M_PI) / static_cast<float>(slices);
        glVertex3f(topRad * std::cos(angle), height, topRad * std::sin(angle));
    }
    glEnd();

    // Tapa inferior
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    for (int i = slices - 1; i >= 0; --i) {
        float angle = static_cast<float>(i) * 2.0f * static_cast<float>(M_PI) / static_cast<float>(slices);
        glVertex3f(baseRad * std::cos(angle), 0.0f, baseRad * std::sin(angle));
    }
    glEnd();
}

void Model::drawSphere(float radius, int slices, int stacks) {
    for (int i = 0; i < stacks; ++i) {
        float lat0 = static_cast<float>(M_PI) * (-0.5f + static_cast<float>(i) / static_cast<float>(stacks));
        float z0 = radius * std::sin(lat0);
        float zr0 = radius * std::cos(lat0);

        float lat1 = static_cast<float>(M_PI) * (-0.5f + static_cast<float>(i + 1) / static_cast<float>(stacks));
        float z1 = radius * std::sin(lat1);
        float zr1 = radius * std::cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; ++j) {
            float lng = 2.0f * static_cast<float>(M_PI) * static_cast<float>(j) / static_cast<float>(slices);
            float x = std::cos(lng);
            float y = std::sin(lng);

            // Normal radial unitaria para sombreado suave de Phong
            glNormal3f(x * std::cos(lat0), std::sin(lat0), y * std::cos(lat0));
            glVertex3f(x * zr0, z0, y * zr0);

            glNormal3f(x * std::cos(lat1), std::sin(lat1), y * std::cos(lat1));
            glVertex3f(x * zr1, z1, y * zr1);
        }
        glEnd();
    }
}

void Model::drawTexturedQuad(float width, float height) {
    float hw = width * 0.5f;
    float hh = height * 0.5f;

    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-hw, -hh, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( hw, -hh, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( hw,  hh, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-hw,  hh, 0.0f);
    glEnd();
}