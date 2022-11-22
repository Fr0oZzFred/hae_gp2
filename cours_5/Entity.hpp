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
	int yOffset = -100;

	Ball(Pad* pad) : Entity(new sf::CircleShape(50),
		new sf::Vector2f(50, 50)) {
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

class Particle {
public:
	sf::Vector2f position;
	float duration = .5;
	float timeSinceCreation = 0;
	bool used = true;
	int qual = 16;
	float distanceMin = 20;
	float distanceRand = 30;

	sf::VertexArray shape;

	sf::Vector2f getAngle(float pi) {
		return sf::Vector2f(std::cos(pi), std::sin(pi));
	};

	Particle(sf::Vector2f pos) {
		position = pos + sf::Vector2f(100,25); //offset psk pas d'origin
		CreateParticle();
	};

	void CreateParticle() {
		sf::Vector2f posFix = sf::Vector2f(0, 0);
		sf::VertexArray explosion(sf::PrimitiveType::TriangleStrip, qual + 1);
		for (int i = 0; i < qual; i++) {
			double t = (double)i / qual;
			t *= 3.14159 * 2;
			explosion[i].position = position + getAngle(t) * (distanceMin + (float)Lib::rand() / RAND_MAX * distanceRand);
			if (i == 0) posFix = explosion[i].position;
		}
		explosion[qual].position = posFix;
		shape = explosion;
	};

	void Update(sf::Time dt) {
		timeSinceCreation += dt.asSeconds();

		sf::Vector2f posFix = sf::Vector2f(0, 0);
		for (int i = 0; i < qual; i++) {
			double t = (double)i / qual;
			t *= 3.14159 * 2;
			shape[i].position = position + getAngle(t) * (distanceMin + (float)Lib::rand() / RAND_MAX * distanceRand);
			if (i == 0) posFix = shape[i].position;
		}
		shape[qual].position = posFix;

		if (timeSinceCreation > duration) {
			position = sf::Vector2f(-500, -500);
			used = false;
		}
	};
	void Reset(sf::Vector2f p) {
		timeSinceCreation = 0;
		position = p;
	};
};