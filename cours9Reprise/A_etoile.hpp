#pragma once
#include <unordered_map>
#include <algorithm>

#include "SFML/System/Vector2.hpp"
#include "imgui.h"
#include "imgui-SFML.h"

//namespace std {
//	template <> struct hash<sf::Vector2i> {
//		inline std::size_t operator()(const sf::Vector2i& k) const {
//			using std::hash;
//			return std::size_t((k.y << 12) | k.x);
//		};
//	};
//};

typedef std::unordered_map<sf::Vector2i, bool>	BaseGraph;
typedef std::unordered_map<sf::Vector2i, int> CoutGraph;
typedef std::unordered_map<sf::Vector2i, float> DistanceGraph;
typedef std::unordered_map<sf::Vector2i, sf::Vector2i>	AssocGraph;

class A_etoile {
public:
	sf::Vector2i start	=	sf::Vector2i (-1, -1);
	sf::Vector2i end	=	sf::Vector2i (-1, -1);
	BaseGraph g;
	CoutGraph c;
	DistanceGraph d;
	AssocGraph pred;

	A_etoile() {

	};

	void setGraph(BaseGraph& _g) {
		g = _g;
		d.clear();
		c.clear();
		for (auto& p : g) {
			c[p.first] = 0;
		}
	};

	void init(sf::Vector2i _start) {
		start = _start;
	};

	int compare(sf::Vector2i v1, sf::Vector2i v2) {
		return d[v1] - d[v2];
	};

	void build(sf::Vector2i _start) {
		init(_start);

		std::vector<sf::Vector2i> closedList;
		std::vector<sf::Vector2i> openList;

		auto find = [](sf::Vector2i p, std::vector<sf::Vector2i> list) {
			for (auto& v : list) {
				if ((v.x == p.x) && (v.y == p.y)) return true;
			}
			return false;
		};

		openList.push_back(_start);
		int idx = 0;
		while (!openList.empty()) {
			auto u = openList[idx];
			if ((u.x == end.x) && (u.y == u.y)) {
				//reconstituerChemin
				return;
			}


			sf::Vector2i neighbours[4] = {
				sf::Vector2i(0,1),
				//sf::Vector2i(1,1),
				sf::Vector2i(1,0),
				//sf::Vector2i(1,-1),
				sf::Vector2i(0,-1),
				//sf::Vector2i(-1,-1),
				sf::Vector2i(-1,0),
				//sf::Vector2i(-1,1),
			};

			for (auto& v : neighbours) {
				if (!(find(v, closedList) || (find(v, openList) && c[u] > c[v]))) {
					c[v] = c[u] + 1;
					d[v] = c[v] + (v.x * end.x + v.y * end.y);
					openList.push_back(v);
				}
			}

			closedList.push_back(u);
		}
	}

	void im() {
		using namespace ImGui;
		Value("start x", start.x);
		Value("start y", start.y);
		DragInt2("End", &end.x);
	}
};