#pragma once

#include "AllegroInitializer.h"

class Sound
{
protected:
	ALLEGRO_SAMPLE *starSoundsEffect;
	ALLEGRO_SAMPLE *backgroundSong;
	ALLEGRO_SAMPLE_INSTANCE *songInstance;
	bool soundsLoaded, soundsPrepared;
public:
	Sound();
	~Sound();
	void attachSamples(ALLEGRO_SAMPLE *backgroundSong, ALLEGRO_SAMPLE *starSoundEffect);
	void prepare();
	void playStarSoundEffect();
	void playBackgroundMusic();
};
 