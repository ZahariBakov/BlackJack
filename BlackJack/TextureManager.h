#pragma once

#include <SDL.h>
#include <map>
#include <string>

class TextureManager {
private:
	TextureManager() {};

public:
	auto LoadTexture(const char* fileName, std::string id, SDL_Renderer* ren) -> bool;

	void DrawTexture(std::string id, int xpos, int ypos, int width, int height, SDL_Renderer* ren, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	void DrawRecnatgle(SDL_Renderer* renderer, int xpos, int ypos, int width, int height);

	static TextureManager* Instance();

private:
	std::map<std::string, SDL_Texture*> m_textureMap;
	
	static TextureManager* m_instance;
};
