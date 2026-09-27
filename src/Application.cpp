#include "Application.hpp"
#include <iostream>

#if defined(__APPLE__)
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

Application* Application::instance = nullptr;

Application::Application(int width, int height, const char* title, int argc, char** argv)
    : windowWidth(width), windowHeight(height), previousTimeMs(0) {
    instance = this;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(80, 80);
    glutCreateWindow(title);

    scene.init();

    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshapeCallback);
    glutKeyboardFunc(keyboardCallback);
    glutSpecialFunc(specialCallback);
    glutTimerFunc(16, timerCallback, 0); // 60 FPS aprox
}

void Application::displayCallback() {
    if (instance) {
        instance->scene.render(instance->camera);
    }
}

void Application::reshapeCallback(int w, int h) {
    if (instance) {
        instance->windowWidth = w;
        instance->windowHeight = h;
        instance->camera.applyProjection(w, h);
    }
}

void Application::timerCallback(int value) {
    (void)value;
    if (instance) {
        int currentTimeMs = glutGet(GLUT_ELAPSED_TIME);
        float deltaTime = static_cast<float>(currentTimeMs - instance->previousTimeMs) / 1000.0f;
        instance->previousTimeMs = currentTimeMs;

        // Limite para evitar saltos bruscos tras pausas
        if (deltaTime > 0.1f) deltaTime = 0.016f;

        instance->scene.update(deltaTime);
        glutPostRedisplay();
        glutTimerFunc(16, timerCallback, 0);
    }
}

void Application::keyboardCallback(unsigned char key, int x, int y) {
    (void)x; (void)y;
    if (!instance) return;

    switch (key) {
        // Alternar Luz 1 / recien me di cuenta que pude y debi haber usado el proyecto del pa2
        case 'l':
        case 'L':
            instance->scene.getLight().togglePointLight();
            std::cout << "[Luz 1] " << (instance->scene.getLight().isPointLightEnabled() ? "ENCENDIDA" : "APAGADA") << std::endl;
            break;

        // Trasladar posicion de la Luz 1 en X
        case 'j':
        case 'J':
            instance->scene.getLight().movePointLightX(-0.3f);
            break;
        case 'k':
        case 'K':
            instance->scene.getLight().movePointLightX(0.3f);
            break;

        // Conmutar material del Orbe
        case 'm':
        case 'M':
            instance->scene.cycleOrbMaterial();
            break;

        // Conmutar modelo de sombreado entre Smooth vs Flat
        case 's':
        case 'S':
            instance->scene.toggleShading();
            break;

        // Activar / desactivar textura
        case 't':
        case 'T':
            instance->scene.toggleTexture();
            std::cout << "[Textura] Conmutada" << std::endl;
            break;

        // Inspeccion del Depth Buffer entre activar y desactivar Z-Buffer
        case 'b':
        case 'B':
            instance->scene.toggleDepthTest();
            std::cout << "[Depth Buffer] Z-Test conmutado" << std::endl;
            break;

        // Alternar vistas de camara
        case 'v':
        case 'V':
            instance->camera.nextViewPreset();
            break;

        // Zoom de camara
        case '+':
        case '=':
            instance->camera.zoom(-0.5f);
            break;
        case '-':
        case '_':
            instance->camera.zoom(0.5f);
            break;

        case 27: // Tecla ESC
            std::exit(0);
            break;
    }
    glutPostRedisplay();
}

void Application::specialCallback(int key, int x, int y) {
    (void)x; (void)y;
    if (!instance) return;

    switch (key) {
        case GLUT_KEY_LEFT:  instance->camera.rotate(-4.0f, 0.0f); break;
        case GLUT_KEY_RIGHT: instance->camera.rotate(4.0f, 0.0f);  break;
        case GLUT_KEY_UP:    instance->camera.rotate(0.0f, 3.0f);  break;
        case GLUT_KEY_DOWN:  instance->camera.rotate(0.0f, -3.0f); break;
    }
    glutPostRedisplay();
}

void Application::run() {
    std::cout << "\n"
              << " PA3: Erwin Alain Felix Tayro Mosqueira\n"
              << "\n"
              << " Controles de Experimentacion:\n"
              << "  [L]     : Encender / Apagar Luz 1 Puntual\n"
              << "  [J / K] : Mover Luz 1 a la izquierda / derecha (Eje X)\n"
              << "  [M]     : Cambiar material del Orbe\n"
              << "  [S]     : Alternar sombreado (SMOOTH Phong / FLAT)\n"
              << "  [T]     : Activar / Desactivar textura del panel mural\n"
              << "  [B]     : Activar / Desactivar Depth Buffer (Oclusion)\n"
              << "  [V]     : Alternar entre las 3 vistas de camara\n"
              << "  [Flechas]: Orbitar la camara libremente\n"
              << "  [+ / -] : Zoom de camara\n"
              << "  [ESC]   : Salir\n"
              << "" << std::endl;
    glutMainLoop();
}