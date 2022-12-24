#pragma once
#include <vector>
#include "UiElement.hpp"
#include "Button.hpp"

class Data {
public:
	static inline const char* MAIN_PATH = "res/";
	static bool saveUI(const char* path, std::vector<UiElement*>& elements);
    static std::vector<UiElement*> loadUI(const char* path);
};