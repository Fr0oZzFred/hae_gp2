#pragma once

class Entity {
public:
	sf::Shape* 		shape = nullptr;	// pour le rendu
	sf::Vector2f*	size;
	sf::FloatRect	box;				//pour les collisions
	sf::Vector2f velocity = sf::Vector2f(200, -200);


	Entity(sf::Shape* shape, sf::Vector2f* size) {
		this->shape = shape;
		this->size = size;
		box = shape->getGlobalBounds();
	};

	void UpdateBox() {
		box.left = shape->getPosition().x;
		box.top = shape->getPosition().y;
	}
};

class Pad : public Entity {
public:
	Pad(sf::Vector2f pos) : Entity(new sf::RectangleShape(sf::Vector2f(200, 50)),
		new sf::Vector2f(200, 50)) {
		shape->setPosition(pos);
		UpdateBox();
	};

	void Move(float speed, sf::Time dt, sf::Vector2f screenSize) {
		sf::Vector2f pos = shape->getPosition();
		pos.x += sf::Keyboard::isKeyPressed(sf::Keyboard::Right) * dt.asSeconds() * speed;
		pos.x -= sf::Keyboard::isKeyPressed(sf::Keyboard::Left) * dt.asSeconds() * speed;

		float minX = 0;
		float maxX = screenSize.x - size->x;
		if (pos.x < minX)   pos.x = minX;
		if (pos.x > maxX)   pos.x = maxX;

		shape->setPosition(pos);

		UpdateBox();
	};

	void DetectColision(Entity* ball) {
		if (box.intersects(ball->box)) {
			ball->velocity.y = std::abs(ball->velocity.y) * -1;
			shape->setFillColor(sf::Color::Green);
		}
		else
			shape->setFillColor(sf::Color::Red);
	}
};
class Ball : public Entity {
public:
	Pad* pad = nullptr;
	int yOffset = -50;

	Ball(Pad* pad) : Entity(new sf::CircleShape(25),
		new sf::Vector2f(25, 25)) {
		shape->setPosition(pad->shape->getPosition() + sf::Vector2f(0, yOffset));
		UpdateBox();
	};

	void Move(float speed, sf::Time dt, sf::Vector2f screenSize) {

		sf::Vector2f pos = shape->getPosition();

		pos += velocity * dt.asSeconds();

		float minX = 0;
		float maxX = screenSize.x - size->x;
		float minY = 0;
		float maxY = screenSize.y - size->y;
		if (pos.x < minX)   velocity.x = std::abs(velocity.x);
		if (pos.x > maxX)   velocity.x = std::abs(velocity.x) * -1;
		if (pos.y < minY)	velocity.y = std::abs(velocity.y);
		if (pos.y > maxY)   velocity.y = std::abs(velocity.y) * -1;

		shape->setPosition(pos);

		UpdateBox();
	};
};

class Block : public Entity {
public:
	bool touched = false;
	sf::Vector2f originalPos;

	Block(sf::Vector2f pos) : Entity(new sf::RectangleShape(sf::Vector2f(200, 50)), new sf::Vector2f(200, 50)) {
		shape->setPosition(pos);
		originalPos = pos;
		UpdateBox();
	};
	void DetectColision(Entity* ball) {
		if (box.intersects(ball->box)) {
			ball->velocity.y = std::abs(ball->velocity.y);
			shape->setFillColor(sf::Color::Black);
			shape->setPosition(-500, -500);
			UpdateBox();
			touched = true;
		}
		else
			shape->setFillColor(sf::Color::Red);
	}
};

class Part : public Entity {
public:
	Part(float rotRad, sf::Vector2f newVelocity, sf::Vector2f pos) : Entity(new sf::RectangleShape(sf::Vector2f(10, 5)), new sf::Vector2f(10, 5)) {
		velocity = newVelocity;
		shape->setPosition(pos);
		shape->setOrigin(5, 2.5);
		shape->setRotation(rotRad * 360 / (3.14159 * 2));
	};

	void Update(sf::Time dt) {
		sf::Vector2f pos = shape->getPosition();
		pos += velocity * dt.asSeconds();
		shape->setPosition(pos);
	};
	void Hide() {
		shape->setPosition(sf::Vector2f(-500, -500));
		velocity = sf::Vector2f(0, 0);
	};
};

class Particle {
public:
	sf::Vector2f position;
	float duration = .5;
	float timeSinceCreation = 0;
	bool used = true;
	int qual = 16;
	float distanceMin = 1;
	float distanceRand = 10;

	sf::ConvexShape shape;
	std::vector<Part> rects;

	sf::Vector2f getAngle(float pi) {
		return sf::Vector2f(std::cos(pi), std::sin(pi));
	};

	Particle(sf::Vector2f pos) {
		position = pos + sf::Vector2f(100,25); //offset psk pas d'origin
		CreateParticle();
	};

	void CreateParticle() {
		sf::Vector2f posFix = sf::Vector2f(0, 0);
		sf::ConvexShape explosion(qual + 1);
		sf::RectangleShape rect;
		for (int i = 0; i < qual; i++) {
			double t = (double)i / qual;
			t *= 3.14159 * 2;

			explosion.setPoint(i , position + getAngle(t) * (distanceMin + (float)Lib::rand() / RAND_MAX * distanceRand));
			if (i == 0) posFix = explosion.getPoint(i);


			Part rect(std::sin(t), getAngle(t) * 200.0f, position);
			rect.shape->setFillColor(sf::Color::Red);
			rects.push_back(rect);
		}
		explosion.setPoint(qual, posFix);
		shape = explosion;
	};

	void Update(sf::Time dt) {
		if (!used) return;
		timeSinceCreation += dt.asSeconds();

		auto lerp = [](sf::Color c1, sf::Color c2, float t) {
			sf::Color nuColor(
				c1.r + t * (c2.r - c1.r),
				c1.g + t * (c2.g - c1.g),
				c1.b + t * (c2.b - c1.b)
			);
			return nuColor;
		};


		sf::Vector2f posFix = sf::Vector2f(0, 0);
		for (int i = 0; i < qual; i++) {
			double t = (double)i / qual;
			t *= 3.14159 * 2;
			float sizeByLifetime = 1 + timeSinceCreation * 20;
			float dist = (distanceMin * sizeByLifetime + (float)Lib::rand() / RAND_MAX * distanceRand * sizeByLifetime);
			shape.setPoint( i , position + getAngle(t) * dist);
			if (i == 0) posFix = shape.getPoint(i);

			float colorT = (dist - distanceMin * sizeByLifetime) / (distanceRand * sizeByLifetime - distanceMin * sizeByLifetime);
			shape.setFillColor(lerp(sf::Color::Yellow, sf::Color::Red, colorT));

		}
		shape.setPoint(qual, posFix);
		for (auto &r : rects) {
			r.Update(dt);
		}


		if (timeSinceCreation > duration) {
			position = sf::Vector2f(-500, -500);
			used = false;
			for (int i = 0; i < qual+1; i++) {
				shape.setPoint(i, position);
			}
			for (auto& r : rects) {
				r.Hide();
			}
		}
	};
	void Reset(sf::Vector2f p) {
		timeSinceCreation = 0;
		position = p + sf::Vector2f(100, 25); //offset psk pas d'origin
		for (int i = 0; i < qual; i++) {
			double t = (double)i / qual;

			t *= 3.14159 * 2;
			rects[i].shape->setRotation(std::sin(t) * 360 / (3.14159 * 2));
			rects[i].velocity = getAngle(t) * 200.0f;
			rects[i].shape->setPosition(position);
		}
		used = true;
	};
};