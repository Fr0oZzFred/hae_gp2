#pragma once
#include <vector>
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Line {
public:
	std::vector<sf::Vector2f> origins;
	std::vector<sf::Vector2f> baked;
	
	bool enableControlPointsDisplay = false;



	Line(){
		baked.push_back(sf::Vector2f(200, 200));
		baked.push_back(sf::Vector2f(300, 250));
		baked.push_back(sf::Vector2f(400, 200));
		baked.push_back(sf::Vector2f(500, 200));
	}

	void translate(sf::Vector2f tr) {
		for (auto& t : origins)
			t += tr;
		std::vector<sf::Vector2f> nu = (origins);
		setPoints(nu);
	};

	void rebake(){
		std::vector<sf::Vector2f> nu = (origins);
		setPoints(nu);
	}

	void draw(sf::RenderWindow& win) {
		sf::VertexArray vb(sf::LineStrip);
		for (auto& b : baked) {

			sf::Color c;
			if (b.y < heightMinMax[0])
				c = colorMinMax[0];
			else if (b.y >= heightMinMax[1])
				c = colorMinMax[1];
			else {
				float t = (b.y - heightMinMax[0]) / (heightMinMax[1] - heightMinMax[0]);
				c = sf::Color( 
					Lib::lerp(colorMinMax[0].r, colorMinMax[1].r,t),
					Lib::lerp(colorMinMax[0].g, colorMinMax[1].g,t),
					Lib::lerp(colorMinMax[0].b, colorMinMax[1].b,t)
				);
			}

			sf::Vertex vtx(b, c);

			vb.append(vtx);//tout mes vertex;
		}
		
		win.draw(vb);

		if (enableControlPointsDisplay) {
			for (auto& b : origins) {
				sf::CircleShape ctrl(8);
				ctrl.setOrigin(8, 8);
				ctrl.setPosition(b);
				ctrl.setFillColor(sf::Color(0xFF4CE7ff));
				ctrl.setOutlineColor(sf::Color(0x8AFE2Bff));
				ctrl.setOutlineThickness(2);
				win.draw(ctrl);
			}
		}
	};

	sf::Vector2f get(int idx) {
		if (idx < 0) idx = 0;
		if (idx >= origins.size())idx = origins.size() - 1;
		return origins[idx];
	};

	void setPoints(std::vector<sf::Vector2f>& p, float tstep = 0.1f) {
		origins = p;
		baked.clear();
		int steps = std::round(1.0f / tstep);
		double cstep = 0.0;
		for (int i = 0; i < p.size(); ++i) {
			auto p0 = get(i - 1);
			auto p1 = get(i);
			auto p2 = get(i + 1);
			auto p3 = get(i + 2);
			cstep = 0.0;
			//creer les vertex interpolées entre les courbes.
			while(cstep < 1.0f){
				if (cstep >= 1.0f)
					cstep = 1.0f;
				baked.push_back(Catmull::polynom2(p0, p1, p2, p3, cstep));
				cstep += tstep;
				if (cstep > 1.0f)
					break;
			}
		}
	};


	sf::Color colorMinMax[2] = { sf::Color::White , sf::Color::White };
	float heightMinMax[2] = {150,300};
	

	sf::Vector2f interpolateCatmull(float t) {
		// 0 1 => sur toute la  courbe
		// 0 n ( n = nombre de point
		// 2.5 
		// => interpoler entre 2 et 3 avec un t de 0.5
		float globalT = t * origins.size();
		int i = (int)globalT;
		float localT = globalT - i;
		auto p0 = get(i - 1);
		auto p1 = get(i);
		auto p2 = get(i + 1);
		auto p3 = get(i + 2);
		return Catmull::polynom2(p0, p1, p2, p3, localT);
	};
	
	sf::Vector2f interpolateLinear(float t) {
		// t compris 0 - 1 
		// 0 n nb point baked
		// interpole lineairement entre les deux pos bake avant et apres 
		//
		float globalT = t * (baked.size()-1);
		int i = (int)globalT;//partie entiere entre 0 et n
		float localT = globalT - i;// partie fractionnelle
		if (t >= 1.0f)
			return baked.back();
		if (localT <= 0)
			return baked[i];
		if (localT >= 1)
			return baked[i+1];
		return Lib::lerp(baked[i], baked[i + 1], localT);
	}


};