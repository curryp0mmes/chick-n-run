#include "Sounds.h"



Sounds::Sounds()
{
	sounds.push_back(GameAudio("jump.wav"));
}

void Sounds::play(availableSounds sound)
{
	sounds[sound].play();
}


Sounds::~Sounds()
{
}
