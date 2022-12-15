#pragma once
#include <unordered_map>
#include <algorithm>

#include "SFML/System/Vector2.hpp"
#include "imgui.h"
#include "imgui-SFML.h"

namespace std {
	template <> struct hash<sf::Vector2i> {
		inline std::size_t operator()(const sf::Vector2i& k) const {
			using std::hash;
			return std::size_t((k.y << 12) | k.x);
		};
	};
};

typedef std::unordered_map<sf::Vector2i, bool>	BaseGraph;
typedef std::unordered_map<sf::Vector2i, float> CoutGraph;
typedef std::unordered_map<sf::Vector2i, float> DistanceGraph;
typedef std::unordered_map<sf::Vector2i, sf::Vector2i>	AssocGraph;

class A_etoile {
public:
	sf::Vector2i start	=	sf::Vector2i (-1, -1);
	sf::Vector2i end	=	sf::Vector2i (-1, -1);
	BaseGraph g;
	DistanceGraph d;
	AssocGraph pred;

	A_etoile() {

	};

	void setGraph(BaseGraph& _g) {
		g = _g;
		d.clear();
	};

	void init(sf::Vector2i _start) {
		start = _start;
	};

	int compare(sf::Vector2i v1, sf::Vector2i v2) {
		return d[v1] - d[v2];
	};

	void build(sf::Vector2i _start) {
		init(_start);
	}

	void im() {
		using namespace ImGui;
		Value("start x", start.x);
		Value("start y", start.y);
		DragInt2("End", &end.x);
	}
};