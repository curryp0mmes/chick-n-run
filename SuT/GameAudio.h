#pragma once
#include "defines.h"
#include <SFML/Audio.hpp>
using namespace sf;
using namespace std;
class GameAudio
{
public:
	GameAudio(string file);
	void play() { sound.play(); }
	void pause() { sound.pause(); }
	void stop() { sound.stop(); }
	
	
	~GameAudio();
private:
	Sound sound;
	SoundBuffer buffer;
	string filename;
};

