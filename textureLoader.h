#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include "raylib.h"
#include <iostream>
#include <vector>
#include <unordered_map>

class TextureLoader {
public:
    TextureLoader();
    void loadTexture(std::string key, std::string path);
    void unloadTexture(std::string path);
    void unloadTextures();
    Texture2D getTexture(std::string key);
protected:



private:
    std::unordered_map<std::string, Texture2D> storage;
};

#endif // !TEXTURELOADER_H