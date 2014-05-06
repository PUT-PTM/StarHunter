#include "Sound.h"

Sound::Sound(){
	soundsLoaded = false;
	soundsPrepared = false;
}

Sound::~Sound(){
	al_destroy_sample_instance(songInstance);
};

void Sound::attachSamples(ALLEGRO_SAMPLE *backgroundSong, ALLEGRO_SAMPLE *starSoundEffect){
	this->backgroundSong = backgroundSong;
	this->starSoundsEffect = starSoundEffect;
	soundsLoaded = true;
}

void Sound::prepare(){
	if(soundsLoaded){
		al_reserve_samples(2);
		soundsPrepared = true;

		songInstance = al_create_sample_instance(backgroundSong);
		al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
		al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());
	}
	else
		throw MyException("Sounds was not attached.");
}

void Sound::playStarSoundEffect(){
	if(soundsPrepared)
		al_play_sample(this->starSoundsEffect, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
}

void Sound::playBackgroundMusic(){
	if(soundsPrepared)
		al_play_sample_instance(songInstance);
}



