#include "Sound.hpp"

string errorToString(ALuint error);

Sound::Sound(string filename)
	: error(AL_NO_ERROR)
{
	ALenum format;
	ALsizei size;
	ALsizei freq;
	ALboolean loop;
	ALvoid* data;

	alGenBuffers(1, &(this->buffer));
	if(hasError()) return;

	alutLoadWAVFile((ALbyte*) filename.c_str(), &format, &data, &size, &freq, &loop);
	if(hasError()) return;

	alBufferData(this->buffer, format, data, size, freq);
	if(hasError()) return;

	alutUnloadWAV(format,data,size,freq);
	if(hasError()) return;

	alGenSources(1, &(this->source));
	if(hasError()) return;

	alSourcei(source, AL_BUFFER, buffer);
	if(hasError()) return;
}

Sound::~Sound()
{
	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);
}

bool Sound::play(int volume)
{
	if(volume < 0 || volume > 100)
	{
		std::cout << "Requested volume of " << volume << " is out of range" << std::endl;
		return !hasError();
	}

	//Apply Master Volume Setting
	alSourcef(source, AL_GAIN, (float) (volume/100));
	alSourcePlay(source);
	return !hasError();
}

bool Sound::stop()
{
	alSourceStop(source);
	return !hasError();
}

bool Sound::rewind()
{
	alSourceRewind(source);
	return !hasError();
}

bool Sound::pause()
{
	alSourcePause(source);
	return !hasError();
}

bool Sound::hasError()
{
	ALuint nextError = alGetError();

	//If there is a new error, update it
	if((error != AL_NO_ERROR && nextError != AL_NO_ERROR && nextError != error) || (error == AL_NO_ERROR))
	{
		error = nextError;
	}

	if(error != AL_NO_ERROR)
	{
		return true;
	}
	return false;
}

void Sound::clearError()
{
	error = AL_NO_ERROR;
}

string errorToString(ALuint error)
{
	switch(error)
	{
		case AL_NO_ERROR: 			return "AL_NO_ERROR";
		case AL_INVALID_NAME: 		return "AL_INVALID_NAME";
		case AL_INVALID_ENUM: 		return "AL_INVALID_ENUM";
		case AL_INVALID_VALUE: 		return "AL_INVALID_VALUE";
		case AL_INVALID_OPERATION: 	return "AL_INVALID_OPERATION";
		case AL_OUT_OF_MEMORY: 		return "AL_OUT_OF_MEMORY";
		default:		  			return "UNKNOWN_ERROR";
	}
}