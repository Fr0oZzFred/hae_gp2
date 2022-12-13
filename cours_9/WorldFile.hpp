#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>
#include <iostream>

class WorldFile {
public:
    static std::vector<sf::Vector2i> load(const char* path) {
        std::vector<sf::Vector2i> walls;
        std::FILE* file;
        fopen_s(&file, path, "r");

        if (!file) return walls;

        while (!feof(file)) {
            sf::Vector2i w;
            fscanf_s(file, "%i %i \n", &w.x, &w.y);
            walls.push_back(w);
        }

        fclose(file);
        return walls;
    };

    static bool save(const char* path, std::vector<sf::Vector2i>& data) {
        std::FILE* file;
        fopen_s(&file, path, "w");
        if (!file) std::ofstream{ path };

        for (auto w : data) {
            fprintf(file, "%i %i \n", w.x, w.y);
        }
        fclose(file);

        return true;
    };
};