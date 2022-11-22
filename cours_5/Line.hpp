#pragma once

class Line {
public:

	void draw(sf::RenderWindow& win) {
		sf::VertexArray vb(sf::LinesStrip);
		for (auto p : baked) {
			sf::Vertex vtx(p, sf::Color::Cyan);
			vb.append(vtx);
		}
		win.draw(vb);
	}


	void setPoints(std::vector <sf::Vector2f>& p, float tResolution = 0.1f) {
		auto get = [&p](int idx) {
			if (idx < 0) idx = 0;
			if (idx >= p.size()) idx = p.size() - 1;
			return p[idx];
		};
		baked.clear();
		double steps = std::ceil(1.0 / tResolution);
		double cstep = 0.0;
		for (int i = 0; i < p.size() - 1; i++) {
			auto p0 = get(i - 1);
			auto p1 = get(i);
			auto p2 = get(i + 1);
			auto p3 = get(i + 2);
			cstep = 0.0;
			for (int i = 0; i < steps; i++) {
				baked.push_back(Catmull::polynom2(p0, p1, p2, p3, cstep));
				cstep += tResolution;
			}
		}
	};

	sf::Vector2f getPoint(float t = 0) {
		if (t < 0) return baked[0];
		if (t > baked.size() - .25) return baked[baked.size()];
		return baked[(int)baked.size() * (t + .25)];
	};
private:
	std::vector <sf::Vector2f> baked;

	sf::CircleShape CreateRec(sf::Vector2f p) {
		sf::CircleShape p0(4);
		p0.setOrigin(2,2);
		p0.setFillColor(sf::Color::Green);
		p0.setPosition(p);
		return p0;
	};
};