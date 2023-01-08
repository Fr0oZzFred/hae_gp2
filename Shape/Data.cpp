#include "Data.hpp"
#include <fstream>

bool Data::saveUI(const char* path, std::vector<UiElement*>& elements) {
    std::FILE* file;
    fopen_s(&file, path, "w");
    if (!file) std::ofstream{ path };

    for (auto c : elements) {
        fprintf(file, "%i \n", c->type);
        c->save(file);
    }

    fclose(file);

    return true;
}
bool Data::saveEnemySpawner(const char* path, std::vector<SpawnEnemy>& enemies) {
    std::FILE* file;
    fopen_s(&file, path, "w");
    if (!file) std::ofstream{ path };

    for (auto e : enemies) {
        e.save(file);
    }

    fclose(file);

    return true;
}
;
std::vector<UiElement*> Data::loadUI(const char* path) {
    std::vector<UiElement*> elements;
    std::FILE* file;
    fopen_s(&file, path, "r");

    if (!file) return elements;

    while (!feof(file)) {
        UiElement* e = nullptr;
        int type = -1;
        fscanf_s(file, "%i \n", &type);
        switch (type) {
        default:
        throw "Type out of index";
        elements.clear();
        return elements;
        break;

        case 0:
        e = new Button();
        e->load(file);
        break;
        }
        if (e == nullptr) {
            elements.clear();
            return elements;
        }
        elements.push_back(e);
    }

    fclose(file);
    return elements;
};
std::vector<SpawnEnemy> Data::loadEnemySpawner(const char* path) {
    std::vector<SpawnEnemy> enemies;
    std::FILE* file;
    fopen_s(&file, path, "r");

    if (!file) return enemies;

    while (!feof(file)) {
        SpawnEnemy spawn;
        spawn.load(file);
        enemies.push_back(spawn);
    }

    fclose(file);
    return enemies;
};