#pragma once

#include <vector>

#include "sound.h"

#ifdef SPARKY_EMSCRIPTEN
	#include <emscripten/emscripten.h>
	#include <map>
#else
	#define GAU_THREAD_POLICY_MULTI 2
	#include "../../ext/gorilla-audio/ga.h"
	#include "../../ext/gorilla-audio/gau.h"
#endif

#ifdef SPARKY_EMSCRIPTEN
extern "C" void SoundManagerAdd(const char* name, const char* filename);
extern "C" void SoundManagerPlay(const char* name);
extern "C" void SoundManagerPause(const char* name);
extern "C" void SoundManagerStop(const char* name);
extern "C" void SoundManagerLoop(const char* name);
extern "C" void SoundManagerSetGain(const char* name, double gain);
#endif

namespace sparky { namespace audio {

	class SoundManager
	{
	private:
		friend class Sound;

#ifdef SPARKY_EMSCRIPTEN
#else
		static gau_Manager* m_Manager;
		static ga_Mixer* m_Mixer;
#endif

		static std::vector<Sound*> m_Sounds;
	public:
		static void init();
		static void add(Sound* sound);
		static Sound* get(const std::string& name);
		static void update();
		static void clean();
	private:
		SoundManager() { }
	};

} }