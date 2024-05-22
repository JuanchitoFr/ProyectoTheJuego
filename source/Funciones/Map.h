#include "pch.h"

#ifndef MAP_H
#define MAP_H

const int Max_Size = 50;

namespace map
{
	class SpriteMap
	{
	private:
		std::string keys[Max_Size];
		Sprite sprites[Max_Size];
		int size;
	public:
		SpriteMap() : size(0)
		{
		}
		~SpriteMap()
		{
		}
		Sprite get(const std::string key)
		{
			for (int i = 0; i < size; ++i) {
				if (keys[i] == key) {
					return sprites[i];
				}
			}
			std::cerr << "Error: Key not found!" << std::endl;
			return Sprite();  // Valor por defecto en caso de no encontrar la clave
		}
		void insert(SpriteMap& map, const std::string key, Sprite& sprite)
		{
			for (size_t i = 0; i < size; i++)
			{
				if (keys[i] == key) {
					sprites[i] = sprite;
					return;
				}
			}
			if (size < Max_Size) {
				keys[size] = key;
				sprites[size] = sprite;
				++size;
			}
			else {
				std::cerr << "Error: Map is full!" << std::endl;
			}
		}
		void erase(const std::string key)
		{
			for (int i = 0; i < size; ++i) {
				if (keys[i] == key) {
					// Mover el último elemento a la posición del elemento eliminado
					keys[i] = keys[size - 1];
					sprites[i] = sprites[size - 1];
					--size;
					return;
				}
			}
			std::cerr << "Error: Key not found!" << std::endl;
		}
		size_t getSize() const
		{
			return size;
		}
	

	};
	
	class TextureMap
	{
	private:
		std::string keys[Max_Size];
		Texture* textures[Max_Size];
		int size;
	public:
		TextureMap() : size(0)
		{
		}
		~TextureMap()
		{
		}
		Texture* get(const std::string key)
		{
			for (int i = 0; i < size; ++i) {
				if (keys[i] == key) {
					return textures[i];
				}
			}
			std::cerr << "Error: Key not found!" << std::endl;
			return nullptr;  // Valor por defecto en caso de no encontrar la clave
		}
		void insert(const std::string key, Texture& texture)
		{
			for (size_t i = 0; i < size; i++)
			{
				if (keys[i] == key) {
					textures[i] = &texture;
					return;
				}
			}
			if (size < Max_Size) {
				keys[size] = key;
				textures[size] = &texture;
				++size;
			}
			else {
				std::cerr << "Error: Map is full!" << std::endl;
			}
		}
		void erase(const std::string key)
		{
			for (int i = 0; i < size; ++i) {
				if (keys[i] == key) {
					// Mover el último elemento a la posición del elemento eliminado
					keys[i] = keys[size - 1];
					textures[i] = textures[size - 1];
					--size;
					return;
				}
			}
			std::cerr << "Error: Key not found!" << std::endl;
		}
		size_t getSize() const
		{
			return size;
		}
	

	};

	class IntMap
	{
	private:
		std::string keys[Max_Size];
		int values[Max_Size], size;
	public:
		IntMap() : size(0)
		{
		}
		~IntMap()
		{
		}
		int get(const std::string key)
		{
			for (int i = 0; i < size; ++i) {
				if (keys[i] == key) {
					return values[i];
				}
			}
			std::cerr << "Error: Key not found!" << std::endl;
			return -1;  // Valor por defecto en caso de no encontrar la clave
		}
		void insert(const std::string key, int value)
		{
			for (size_t i = 0; i < size; i++)
			{
				if (keys[i] == key) {
					values[i] = value;
					return;
				}
			}
			if (size < Max_Size) {
				keys[size] = key;
				values[size] = value;
				++size;
			}
			else {
				std::cerr << "Error: Map is full!" << std::endl;
			}
		}
		void erase(const std::string key)
		{
			for (int i = 0; i < size; ++i) {
				if (keys[i] == key) {
					// Mover el último elemento a la posición del elemento eliminado
					keys[i] = keys[size - 1];
					values[i] = values[size - 1];
					--size;
					return;
				}
			}
			std::cerr << "Error: Key not found!" << std::endl;
		}
		size_t getSize() const
		{
			return size;
		}
	};

	
}

#endif // !MAP_H




