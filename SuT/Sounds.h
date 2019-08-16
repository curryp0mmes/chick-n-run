#pragma once
#include "GameAudio.h"
#include "defines.h"
class Sounds
{
public:
	Sounds();
	void play(availableSounds sound);
	~Sounds();
	vector<GameAudio> sounds;
	GameAudio jump = GameAudio("jump.wav");
};

