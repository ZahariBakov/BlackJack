#include "TextureManager.h"
#include <SDL_image.h>

#include <iostream>

TextureManager* TextureManager::Instance() {

	if (m_instance == 0) {
		m_instance = new TextureManager();

		return m_instance;
	}

	return m_instance;
}

bool TextureManager::LoadTexture(const char* fileName, std::string id, SDL_Renderer* ren) 
{
	SDL_Surface* tmpSurface = IMG_Load(fileName);

	if (tmpSurface == 0) {
		std::cout << "tmpSurface not created!" << std::endl;
		return false;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	if (tex != 0) {
		m_textureMap[id] = tex;
		return true;
	}

	return false;
}

void TextureManager::DrawTexture(std::string id, int xpos, int ypos, int width, int height, SDL_Renderer* ren, SDL_RendererFlip flip) 
{
	SDL_Rect srcRect = { 0, 0, 0, 0 };
	SDL_Rect destRect = { 0, 0, 0, 0 };
	srcRect.x = srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = xpos;
	destRect.y = ypos;

	SDL_RenderCopyEx(ren, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::DrawRecnatgle(SDL_Renderer* renderer, int xpos, int ypos, int width, int height) {
	SDL_Rect fillRect = { xpos, ypos, width, height };
	
	SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
	SDL_RenderFillRect(renderer, &fillRect);
}

TextureManager* TextureManager::m_instance = 0;
