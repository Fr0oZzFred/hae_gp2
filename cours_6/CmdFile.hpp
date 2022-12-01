#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "Lib.hpp"
enum class CmdId : int {
    moveForward,
    moveBackward,
    rotateLeft,
    rotateRight,
    draw,
    reset,
};

struct Cmd {
    CmdId id = CmdId::reset;
    float data = 0;
};

class CmdFile {
public:
    static std::vector<Cmd> load(const char* path) {
        std::vector<Cmd> cmds;
        std::FILE* file;
        fopen_s(&file, path, "r");

        if (!file) return cmds;

        while (!feof(file)) {
            Cmd c;
            char id[128] = {};
            fscanf_s(file, "%s %f \n", id, 127, &c.data);
            c.id = stringToCmdId(id);
            cmds.push_back(c);
        }
        
        fclose(file);
        return cmds;
    };

    static bool save(const char* path, std::vector<Cmd> &data) {
        std::FILE* file;
        fopen_s(&file, path, "w");
        if (!file) std::ofstream{ path };

        for (auto c : data) {
            fprintf(file, "%s %f \n", CmdIdToString(c.id) , c.data);
        }
        fclose(file);


        return true;
    };

private:
    static const char* CmdIdToString(CmdId id) {
        if ((int)id == 0) return "moveForward";
        if ((int)id == 1) return "moveBackward";
        if ((int)id == 2) return "rotateLeft";
        if ((int)id == 3) return "rotateRight";
        if ((int)id == 4) return "draw";
        if ((int)id == 5) return "reset";
    }

    static CmdId stringToCmdId(std::string id) {
        if (id == "moveForward")    return CmdId::moveForward;
        if (id == "moveBackward")   return (CmdId)1;
        if (id == "rotateLeft")     return (CmdId)2;
        if (id == "rotateRight")    return (CmdId)3;
        if (id == "draw")           return (CmdId)4;
        if (id == "reset")          return (CmdId)5;
    }
};
