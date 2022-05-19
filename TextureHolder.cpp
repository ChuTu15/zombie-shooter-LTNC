#include "header/TextureHolder.h"
#include <assert.h>

using namespace sf;
using namespace std;

TextureHolder* TextureHolder::s_Instance = nullptr;

TextureHolder::TextureHolder()
{
    assert(s_Instance == nullptr);
    s_Instance = this;
}

sf::Texture& TextureHolder::GetTexture(string const& filename)
{
    auto& m = s_Instance->Textures;
    auto keyValPair = m.find(filename);

    if (keyValPair != m.end())
    {
        return keyValPair->second;
    }
    else
    {
        auto& texture = m[filename];
        texture.loadFromFile(filename);
        return texture;
    }
}
