#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#if defined(__APPLE__)
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

struct MaterialData {
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat shininess;

    void apply() const {
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    }
};

class Material {
public:
    static MaterialData floorStone() {
        return {
            { 0.15f, 0.15f, 0.16f, 1.0f },
            { 0.35f, 0.36f, 0.38f, 1.0f },
            { 0.10f, 0.10f, 0.10f, 1.0f },
            8.0f
        };
    }

    static MaterialData pedestalMarble() {
        return {
            { 0.20f, 0.22f, 0.25f, 1.0f },
            { 0.60f, 0.62f, 0.65f, 1.0f },
            { 0.40f, 0.40f, 0.40f, 1.0f },
            32.0f
        };
    }

    static MaterialData metallicGold() {
        return {
            { 0.25f, 0.20f, 0.07f, 1.0f },
            { 0.85f, 0.65f, 0.15f, 1.0f },
            { 1.00f, 0.90f, 0.60f, 1.0f },
            100.0f
        };
    }

    static MaterialData rubyPlastic() {
        return {
            { 0.25f, 0.05f, 0.05f, 1.0f },
            { 0.80f, 0.15f, 0.15f, 1.0f },
            { 0.70f, 0.50f, 0.50f, 1.0f },
            40.0f
        };
    }

    static MaterialData matteJade() {
        return {
            { 0.10f, 0.20f, 0.12f, 1.0f },
            { 0.25f, 0.65f, 0.35f, 1.0f },
            { 0.05f, 0.05f, 0.05f, 1.0f },
            4.0f
        };
    }

    static MaterialData darkConsole() {
        return {
            { 0.08f, 0.10f, 0.14f, 1.0f },
            { 0.18f, 0.22f, 0.28f, 1.0f },
            { 0.30f, 0.35f, 0.40f, 1.0f },
            25.0f
        };
    }

    static MaterialData brassLamp() {
        return {
            { 0.22f, 0.18f, 0.10f, 1.0f },
            { 0.55f, 0.42f, 0.20f, 1.0f },
            { 0.70f, 0.60f, 0.40f, 1.0f },
            50.0f
        };
    }

    static MaterialData wallPanel() {
        return {
            { 0.25f, 0.25f, 0.25f, 1.0f },
            { 0.75f, 0.75f, 0.75f, 1.0f },
            { 0.20f, 0.20f, 0.20f, 1.0f },
            16.0f
        };
    }
};

#endif // MATERIAL_HPP