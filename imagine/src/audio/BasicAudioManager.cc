/*  This file is part of Imagine.

	Imagine is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Imagine is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Imagine.  If not, see <http://www.gnu.org/licenses/> */

#include <imagine/audio/AudioManager.hh>
#include <imagine/audio/defs.hh>
#include <imagine/base/ApplicationContext.hh>
#include <imagine/logger/logger.h>

namespace IG::AudioManager
{

Audio::SampleFormat nativeSampleFormat(Base::ApplicationContext)
{
	return Audio::SampleFormats::f32;
}

uint32_t nativeRate(Base::ApplicationContext)
{
	return ::Config::MACHINE_IS_PANDORA ? 44100 : 48000;
}

Audio::Format nativeFormat(Base::ApplicationContext app)
{
	return {nativeRate(app), nativeSampleFormat(app), 2};
}

void setSoloMix(Base::ApplicationContext, bool newSoloMix) {}

bool soloMix(Base::ApplicationContext) { return false; }

void setMusicVolumeControlHint(Base::ApplicationContext) {}

void startSession(Base::ApplicationContext) {}

void endSession(Base::ApplicationContext) {}

}

namespace IG::Audio
{

static constexpr ApiDesc apiDesc[]
{
	#ifdef CONFIG_AUDIO_PULSEAUDIO
	{"PulseAudio", Api::PULSEAUDIO},
	#endif
	#ifdef CONFIG_AUDIO_ALSA
	{"ALSA", Api::ALSA},
	#endif
};

std::vector<ApiDesc> audioAPIs(Base::ApplicationContext)
{
	return {apiDesc, apiDesc + std::size(apiDesc)};
}

Api makeValidAPI(Base::ApplicationContext, Api api)
{
	for(auto desc: apiDesc)
	{
		if(desc.api == api)
		{
			logDMsg("found requested API:%s", desc.name);
			return api;
		}
	}
	// API not found, use the default
	return apiDesc[0].api;
}

}
