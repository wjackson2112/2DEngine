#ifndef SOUND_H
#define SOUND_H

#include <AL/alut.h>
#include <string>
#include <iostream>
#include "OptionsManager.hpp"

using namespace std;

class Sound
{
private:
	ALenum error;
	ALuint buffer;
	ALuint source;

public:
	Sound(string filename);
	~Sound();
	bool play(int volume);
	bool stop();
	bool rewind();
	bool pause();

	bool hasError();
	void clearError();
};

string errorToString(ALuint error);

#endif