#pragma once

struct SpawnEnemy {
	float time = 0;
	float shotRate = 0.3f;
	int moving = 0;
	float offsetX = 0, offsetY = 0;
	int side = 0;
	float lerpPos = 0;

	bool operator< (SpawnEnemy b) { return (time < b.time); }
	void im() {
		using namespace ImGui;
			DragFloat("Spawn Time", &time);
			SliderInt("Spawn Side", &side, 0, 3);
			SliderFloat("Spawn Pos", &lerpPos, 0.0f, 1.0f);
			DragFloat2("Offset", &offsetX);
			SliderInt("Moving", &moving, 0, 1);
			DragFloat("Shot Rate", &shotRate);
	};

	void save(FILE* file) {
		fprintf(file, "%f %f %i %f %f %i %f \n",
			time, shotRate, moving,
			offsetX, offsetY,
			side, lerpPos
		);
	};
	void load(FILE* file) {
		fscanf_s(file, "%f %f %i %f %f %i %f \n",
			&time, &shotRate, &moving,
			&offsetX, &offsetY,
			&side, &lerpPos
		);
	};
};