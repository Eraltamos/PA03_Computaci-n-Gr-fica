#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Camera.hpp"
#include "Scene.hpp"

class Application {
private:
    static Application* instance;

    int windowWidth;
    int windowHeight;
    int previousTimeMs;
    Camera camera;
    Scene scene;

    static void displayCallback();
    static void reshapeCallback(int w, int h);
    static void keyboardCallback(unsigned char key, int x, int y);
    static void specialCallback(int key, int x, int y);
    static void timerCallback(int value);

public:
    Application(int width, int height, const char* title, int argc, char** argv);
    void run();

    Camera& getCamera() { return camera; }
    Scene& getScene() { return scene; }
};

#endif // APPLICATION_HPP