#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#if defined(__APPLE__)
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

class Texture {
private:
    GLuint textureID;
    bool isLoaded;

    void generateProceduralCelestialMap();

public:
    Texture();
    ~Texture();

    bool loadBMP(const std::string& filepath);
    void bind() const;
    void unbind() const;

    bool getIsLoaded() const { return isLoaded; }
};

#endif // TEXTURE_HPP