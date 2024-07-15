#include "textureLoader.h"

#include <stdexcept>

TextureLoader::TextureLoader() {
    loadTexture("blankCoin", "textures/blankCoin.png");
    loadTexture("redCoin", "textures/redCheeky.png");
    loadTexture("yellowCoin", "textures/yellowChill.png");
};

void TextureLoader::loadTexture(std::string key, std::string path) {
    try {
        if (storage.find(key) == storage.end()) {
            storage.insert({key, LoadTexture(path.c_str())});
        } else {
            throw std::invalid_argument("key is already in use");
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << '\n';
    }
}

void TextureLoader::unloadTexture(std::string key) {
    try {
        if (storage.find(key) != storage.end()) {
            UnloadTexture(storage.at(key));
        } else {
            throw std::invalid_argument("key does not exist");
        }

    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << '\n';
    }
}

void TextureLoader::unloadTextures() {
    for (auto path : storage) {
        UnloadTexture(path.second);
    }
}

Texture2D TextureLoader::getTexture(std::string key) {
    try {
        if (storage.find(key) != storage.end()) {
            return storage.at(key);
        } else {
            throw std::invalid_argument("key does not exist");
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << '\n';
        return Texture2D{};
    }
}