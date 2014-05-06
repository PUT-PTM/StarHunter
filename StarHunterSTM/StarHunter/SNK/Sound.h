#pragma once

#include "AllegroInitializer.h"

class Sound
{
protected:

	ALLEGRO_SAMPLE *soundEffect;
	ALLEGRO_SAMPLE *song;
	ALLEGRO_SAMPLE_INSTANCE *songInstance;
public:
	~Sound();
	void loadSamples();
	void prepare();
	void playStarSoundEffect();
	void playBackgroundMusic();
};
 