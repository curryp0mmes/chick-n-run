#include "GameAudio.h"



GameAudio::GameAudio(string file) : filename(file)
{
	buffer.loadFromFile(RESPATH "sounds/" + filename);
	sound.setBuffer(buffer);
}


GameAudio::~GameAudio()
{
}
