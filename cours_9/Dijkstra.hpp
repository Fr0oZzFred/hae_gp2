#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Cst.hpp"

class Dijkstra {
public:

	std::vector<sf::Vector2i> g;
	std::vector<float> gd;
	sf::VertexArray	gGfx;
	std::vector<sf::Vector2i> visited;
	sf::VertexArray visitedGfx;
	std::vector<sf::Vector2i> pred;

	Dijkstra() {
		gGfx.setPrimitiveType(sf::Quads);
		visitedGfx.setPrimitiveType(sf::Quads);
	};
	void add(sf::Vector2i pos) {
		g.push_back(pos);
		gd.push_back(1024 * 1024);
	};
	void draw(sf::RenderWindow& win) {
		win.draw(gGfx);
		win.draw(visitedGfx);
	};
	int find(sf::Vector2i pos) {
		int idx = 0;
		for (auto& p : g) {
			if (p == pos) return idx;
			idx++;
		}
		return -1;
	};

	void mkGraphGraphics() {
		sf::Color col = sf::Color(128, 128, 0, 255);
		gGfx.clear();
		for (auto iter = g.begin(); iter != g.end(); ) {
			sf::Vector2i vtx = *iter;
			gGfx.append(sf::Vertex(sf::Vector2f(vtx.x * Cst::CELL_SIZE, vtx.y * Cst::CELL_SIZE), col));
			gGfx.append(sf::Vertex(sf::Vector2f((vtx.x + .9) * Cst::CELL_SIZE, vtx.y * Cst::CELL_SIZE), col));
			gGfx.append(sf::Vertex(sf::Vector2f((vtx.x + .9) * Cst::CELL_SIZE, (vtx.y + .9) * Cst::CELL_SIZE), col));
			gGfx.append(sf::Vertex(sf::Vector2f(vtx.x * Cst::CELL_SIZE, (vtx.y + .9) * Cst::CELL_SIZE), col));
			iter++;
		}
	};
	void mkVisitedGraphics() {
		sf::Color col = sf::Color(255, 0, 255, 255);
		visitedGfx.clear();
		for (auto iter = visited.begin(); iter != visited.end(); ) {
			sf::Vector2i vtx = *iter;
			visitedGfx.append(sf::Vertex(sf::Vector2f(vtx.x * Cst::CELL_SIZE, vtx.y * Cst::CELL_SIZE), col));
			visitedGfx.append(sf::Vertex(sf::Vector2f((vtx.x + .9) * Cst::CELL_SIZE, vtx.y * Cst::CELL_SIZE), col));
			visitedGfx.append(sf::Vertex(sf::Vector2f((vtx.x + .9) * Cst::CELL_SIZE, (vtx.y + .9) * Cst::CELL_SIZE), col));
			visitedGfx.append(sf::Vertex(sf::Vector2f(vtx.x * Cst::CELL_SIZE, (vtx.y + .9) * Cst::CELL_SIZE), col));
			iter++;
		}
	};
	int min(int d1, int d2) {
		if (d1 < 0 && d2) return -1;
		else if  (d1 < 0) return d2;
		else if  (d2 < 0) return d1;
		float dist1 = gd[d1];
		float dist2 = gd[d2];
		if (dist1 < dist2) return d1;
		return d2;
	};
	int min(int d1, int d2, int d3) {
		return min(min(d1, d2), d3);
	};
	int min(int d1, int d2, int d3, int d4) {
		return min(min(d1, d2), min(d3, d4));
	};
	bool findInPred(sf::Vector2i pos) {
		for (auto& p : g) {
			if (p == pos) return true;
		}
		return false;
	};
	void shortestWay(sf::Vector2i start, sf::Vector2i dest) {
		visited.clear();
		visited.push_back(start);
		sf::Vector2i actualPos = start;
		pred.push_back(actualPos);
		int length	= 0;
		bool found	= false;
		auto dist = [](sf::Vector2i a, sf::Vector2i b) {
			sf::Vector2i d = b - a;
			return sqrt(d.x * d.x + d.y * d.y);
		};
		while (!found) {
			length++;
			int idxL = find(actualPos + sf::Vector2i(-1, 0));
			int idxR = find(actualPos + sf::Vector2i(1, 0));
			int idxT = find(actualPos + sf::Vector2i(0, 1));
			int idxB = find(actualPos + sf::Vector2i(0, -1));
			bool hasL = idxL >= 0 && !findInPred(actualPos + sf::Vector2i(-1, 0));
			bool hasR = idxR >= 0 && !findInPred(actualPos + sf::Vector2i(1, 0));
			bool hasT = idxT >= 0 && !findInPred(actualPos + sf::Vector2i(0, 1));
			bool hasB = idxB >= 0 && !findInPred(actualPos + sf::Vector2i(0, -1));
			if (hasL) {
				visited.push_back(actualPos + sf::Vector2i(-1, 0));
				gd[idxL] = dist(actualPos + sf::Vector2i(-1, 0), dest);
			}
			if (hasR) {
				visited.push_back(actualPos + sf::Vector2i(1, 0));
				gd[idxR] = dist(actualPos + sf::Vector2i(1, 0), dest);
			}
			if (hasT) {
				visited.push_back(actualPos + sf::Vector2i(0, 1));
				gd[idxT] = dist(actualPos + sf::Vector2i(0, 1), dest);
			}
			if (hasB) {
				visited.push_back(actualPos + sf::Vector2i(0, -1));
				gd[idxB] = dist(actualPos + sf::Vector2i(0, -1), dest);
			}

			int mini = min(idxL, idxR, idxT, idxB);
			if (mini < 0) found = true;
			actualPos = g[mini];
			pred.push_back(actualPos);
			if (length > 50) found = true;
		}

		mkVisitedGraphics();
	};
};

extern Dijkstra dijkstra;