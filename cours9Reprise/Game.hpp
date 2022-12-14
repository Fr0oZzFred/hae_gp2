#pragma once
struct Game {
public:
	static const int WIDTH ;
	static const int HEIGHT;

	static void playSound(const char* snd);

	static void playExplosion();
	static void playImpact();
	static void	garbage();
};