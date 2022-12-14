#pragma once
#include <string>
#include <vector>

enum class CmdId : int {
	Wall,
};

struct Cmd {
	CmdId	id = CmdId::Wall;
	int		x = 0;
	int		y = 0;
};

class CmdFile{
public:

	static std::vector<Cmd> loadScript(std::string path) {
		std::vector<Cmd> res;
		FILE* f = nullptr;
		fopen_s(&f, path.c_str(), "r");
		if (!f)
			return res;

		int nbRead = 0;
		char cmdName[128] = {};
		do {
			Cmd c;
			c.id = CmdId::Wall;
			c.x = 0.0f;
			c.y = 0.0f;
			cmdName[0] = 0;
			nbRead = fscanf_s(f, "%s %d %d\n", cmdName, 128, &c.x, &c.y);
			if (nbRead > 0)
				res.push_back(c);
		} while (nbRead > 0);
		fclose(f);
		return res;
	};

	static bool saveScript(std::string path, std::vector<Cmd>& data) {
		FILE* f = nullptr;
		fopen_s(&f, path.c_str(), "w");
		if (!f)
			return false;
		for (auto& cmd : data) {
			switch (cmd.id) {
			case CmdId::Wall:		fprintf(f, "Wall %d %d\n",  cmd.x, cmd.y); break;
			default:
				break;
			}
		}
		fflush(f);
		fclose(f);
		return true;
	}
};