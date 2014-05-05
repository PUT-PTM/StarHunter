#include "Sound.h"


Sound::Sound()
{
	

	song = al_load_sample("assets/sounds/background.ogg");
	this->soundEffect = al_load_sample("assets/sounds/star.ogg");
	songInstance = al_create_sample_instance(song);

	al_reserve_samples(2);

	al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());
	al_play_sample_instance(songInstance);
	
};


void Sound::soundEff(){
	al_play_sample(this->soundEffect, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
}

void Sound::music(){
	al_play_sample_instance(songInstance);
}


Sound::~Sound(){
	al_destroy_sample(song);
	al_destroy_sample_instance(songInstance);
	al_destroy_sample(this->soundEffect);
	
};
