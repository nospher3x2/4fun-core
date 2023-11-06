#pragma once
#include <D3d11.h>

struct Texture
{
	const char* name;
	ID3D11ShaderResourceView* resource = nullptr;
	int width = 0;
	int height = 0;

	Texture(const char* name, ID3D11ShaderResourceView* resource, int width, int height)
	{
		this->name = name;
		this->resource = resource;
		this->width = width;
		this->height = height;
	}
};

class TextureManager
{
public:
	explicit TextureManager(ID3D11Device* device)
	{
		this->Device = device;
	}

private:
	ID3D11Device* Device;
};

