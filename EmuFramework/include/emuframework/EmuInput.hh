#pragma once

/*  This file is part of EmuFramework.

	Imagine is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Imagine is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with EmuFramework.  If not, see <http://www.gnu.org/licenses/> */

#include <emuframework/config.hh>
#include <emuframework/inGameActionKeys.hh>
#ifdef CONFIG_EMUFRAMEWORK_VCONTROLS
#include <emuframework/VController.hh>
#endif
#include <imagine/input/Input.hh>
#include <imagine/util/container/VMemArray.hh>

namespace Input
{
class Device;
}

static constexpr unsigned MAX_INPUT_DEVICE_NAME_SIZE = 64;
static constexpr unsigned MAX_KEY_CONFIG_NAME_SIZE = 80;
static constexpr unsigned MAX_KEY_CONFIG_KEYS = 256;
static constexpr unsigned MAX_DEFAULT_KEY_CONFIGS_PER_TYPE = 10;

class InputDeviceConfig;

struct KeyCategory
{
	constexpr KeyCategory() {}
	template <size_t S>
	constexpr KeyCategory(const char *name, const char *(&keyName)[S],
			unsigned configOffset, bool isMultiplayer = false) :
	name(name), keyName(keyName), keys(S), configOffset(configOffset), isMultiplayer(isMultiplayer) {}

	const char *name{};
	const char **keyName{};
	unsigned keys = 0;
	unsigned configOffset = 0;
	bool isMultiplayer = false; // category appears when one input device is assigned multiple players
};

struct KeyConfig
{
	using NameArray = std::array<char, MAX_KEY_CONFIG_NAME_SIZE>;
	using Key = Input::Key;
	using KeyArray = std::array<Key, MAX_KEY_CONFIG_KEYS>;

	Input::Map map{};
	Input::DeviceSubtype devSubtype{};
	NameArray name{};
	KeyArray key_{};

	constexpr KeyConfig() {}
	constexpr KeyConfig(Input::Map map, Input::DeviceSubtype devSubtype, NameArray name, KeyArray key):
		map{map}, devSubtype{devSubtype}, name{name}, key_{key}
	{}
	constexpr KeyConfig(Input::Map map, NameArray name, KeyArray key):
		KeyConfig{map, {}, name, key}
	{}

	void unbindCategory(const KeyCategory &category);
	bool operator ==(KeyConfig const& rhs) const;
	Key *key(const KeyCategory &category);
	const Key *key(const KeyCategory &category) const;

	const KeyArray &key() const
	{
		return key_;
	}

	KeyArray &key()
	{
		return key_;
	}

	static const KeyConfig *defaultConfigsForInputMap(Input::Map map, unsigned &size);
	static const KeyConfig &defaultConfigForDevice(const Input::Device &dev);
	static const KeyConfig *defaultConfigsForDevice(const Input::Device &dev, unsigned &size);
	static const KeyConfig *defaultConfigsForDevice(const Input::Device &dev);
};

namespace EmuControls
{

using namespace Input;

static constexpr unsigned MAX_CATEGORIES = 8;

// Defined in the emulation module
extern const unsigned categories;
extern const unsigned systemTotalKeys;

extern const KeyCategory category[MAX_CATEGORIES];

extern const KeyConfig defaultKeyProfile[];
extern const unsigned defaultKeyProfiles;
extern const KeyConfig defaultWiimoteProfile[];
extern const unsigned defaultWiimoteProfiles;
extern const KeyConfig defaultWiiCCProfile[];
extern const unsigned defaultWiiCCProfiles;
extern const KeyConfig defaultIControlPadProfile[];
extern const unsigned defaultIControlPadProfiles;
extern const KeyConfig defaultICadeProfile[];
extern const unsigned defaultICadeProfiles;
extern const KeyConfig defaultZeemoteProfile[];
extern const unsigned defaultZeemoteProfiles;
extern const KeyConfig defaultAppleGCProfile[];
extern const unsigned defaultAppleGCProfiles;
extern const KeyConfig defaultPS3Profile[];
extern const unsigned defaultPS3Profiles;

void transposeKeysForPlayer(KeyConfig::KeyArray &key, unsigned player);

// common transpose behavior
void generic2PlayerTranspose(KeyConfig::KeyArray &key, unsigned player, unsigned startCategory);
void genericMultiplayerTranspose(KeyConfig::KeyArray &key, unsigned player, unsigned startCategory);

#ifdef __ANDROID__
static constexpr KeyConfig KEY_CONFIG_ANDROID_NAV_KEYS
{
	Input::Map::SYSTEM,
	{"Android Navigation Keys"},
	{
		EMU_CONTROLS_IN_GAME_ACTIONS_ANDROID_NAV_PROFILE_INIT,

		Input::Keycode::UP,
		Input::Keycode::RIGHT,
		Input::Keycode::DOWN,
		Input::Keycode::LEFT,
	}
};
#endif

}
