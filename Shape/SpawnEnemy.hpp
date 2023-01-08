#pragma once

struct SpawnEnemy {
	float time = 0;
	int side = 0;
	float lerpPos = 0;

	bool operator< (SpawnEnemy b) { return (time < b.time); }
	void im() {
		using namespace ImGui;
			DragFloat("Spawn Time", &time);
			SliderInt("Spawn Side", &side, 0, 3);
			SliderFloat("Spawn Pos", &lerpPos, 0.0f, 1.0f);
	};

	void save(FILE* file) {
		fprintf(file, "%f %i %f \n", time, side, lerpPos);
	};
	void load(FILE* file) {
		fscanf_s(file, "%f %i %f \n", &time, &side, &lerpPos);
	};
};