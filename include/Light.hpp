#ifndef LIGHT_HPP
#define LIGHT_HPP

#if defined(__APPLE__)
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

class Light {
private:
    // Luz 0 Direccional para el ambiental global
    GLfloat dirPosition[4];
    GLfloat dirAmbient[4];
    GLfloat dirDiffuse[4];
    GLfloat dirSpecular[4];

    // Luz 1 Puntual local o lampara emisora
    GLfloat pointPosition[4];
    GLfloat pointAmbient[4];
    GLfloat pointDiffuse[4];
    GLfloat pointSpecular[4];

    bool pointLightEnabled;

public:
    Light();

    void init();
    void apply();
    void togglePointLight();
    void movePointLightX(float delta);

    bool isPointLightEnabled() const { return pointLightEnabled; }
    const GLfloat* getPointPosition() const { return pointPosition; }
};

#endif // LIGHT_HPP