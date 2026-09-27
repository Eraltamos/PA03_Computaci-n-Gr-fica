#include "Texture.hpp"
#include <iostream>
#include <fstream>
#include <vector>

Texture::Texture() : textureID(0), isLoaded(false) {}

Texture::~Texture() {
    if (textureID != 0) {
        glDeleteTextures(1, &textureID);
    }
}

void Texture::generateProceduralCelestialMap() {
    const int width = 128;
    const int height = 128;
    std::vector<unsigned char> data(width * height * 3, 0);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int idx = (y * width + x) * 3;
            unsigned char r = 10, g = 15, b = 35; // Fondo azul noche

            // Reticula celeste
            if (x % 16 == 0 || y % 16 == 0) {
                r = 25; g = 50; b = 90;
            }

            // Pseudo-estrellas fijas
            if ((x * 17 + y * 31) % 47 == 0) {
                r = 240; g = 240; b = 255;
            }

            // Marcadores circulares cardinales
            int cx = x - 64, cy = y - 64;
            if (cx * cx + cy * cy > 40 * 40 && cx * cx + cy * cy < 42 * 42) {
                r = 210; g = 170; b = 60;
            }

            data[idx + 0] = r;
            data[idx + 1] = g;
            data[idx + 2] = b;
        }
    }

    if (textureID == 0) {
        glGenTextures(1, &textureID);
    }

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data());
    isLoaded = true;
    std::cout << "[Textura] Generada textura procedimental de calibracion estelar (128x128)." << std::endl;
}

bool Texture::loadBMP(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "[Aviso Textura] No se encontro " << filepath 
                  << ". Activando generador procedimental de respaldo." << std::endl;
        generateProceduralCelestialMap();
        return true;
    }

    unsigned char header[54];
    file.read(reinterpret_cast<char*>(header), 54);
    if (file.gcount() < 54 || header[0] != 'B' || header[1] != 'M') {
        std::cerr << "[Error Textura] Formato BMP no valido. Usando generador procedimental." << std::endl;
        generateProceduralCelestialMap();
        return true;
    }

    int width = *reinterpret_cast<int*>(&(header[0x12]));
    int height = *reinterpret_cast<int*>(&(header[0x16]));
    int dataPos = *reinterpret_cast<int*>(&(header[0x0A]));
    int imageSize = *reinterpret_cast<int*>(&(header[0x22]));

    if (dataPos == 0) dataPos = 54;
    if (imageSize == 0) imageSize = width * height * 3;

    std::vector<unsigned char> data(imageSize);
    file.seekg(dataPos);
    file.read(reinterpret_cast<char*>(data.data()), imageSize);
    file.close();

    // BMP almacena BGR
    for (int i = 0; i < imageSize; i += 3) {
        std::swap(data[i], data[i + 2]);
    }

    if (textureID == 0) {
        glGenTextures(1, &textureID);
    }

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data());
    isLoaded = true;
    std::cout << "[Textura] BMP cargado exitosamente: " << filepath << " (" << width << "x" << height << ")" << std::endl;
    return true;
}

void Texture::bind() const {
    if (isLoaded) {
        glBindTexture(GL_TEXTURE_2D, textureID);
    }
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}