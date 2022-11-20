#pragma once

struct RenderSettings {
	bool Watermark;
	bool Wireframe;
	int xRes;
	int yRes;
	int depth;
	float FOV;
	float xSens;
	float ySens;
	sf::Color DefaultText;
	uint32_t windowMode;
};