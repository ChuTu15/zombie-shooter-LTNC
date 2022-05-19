#pragma once
#ifndef TEXTURE_HOLDER_H_INCLUDE
#define TEXTURE_HOLDER_H_INCLUDE

#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;
using namespace std;

class TextureHolder
{
private:
    map<string, Texture> Textures;
    static TextureHolder* s_Instance;

public:
    TextureHolder();
    static Texture& GetTexture(string const& filename);
};

#endif // TEXTURE_HOLDER_H_INCLUDE
