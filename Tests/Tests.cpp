
#include "AssetManager.hpp"
#include "OptionsManager.hpp"
#include "Sound.hpp"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

/* Asset Manager */

TEST_CASE("AssetManager")
{
	SECTION("Get a Sound")
	{
		Sound* sound = AssetManager::Instance().getAsset<Sound>("./Tests/test_assets/Sound.wav");
		REQUIRE(sound != NULL);
		REQUIRE(sound->hasError() == false);
	}
}

/* Options Manager */
TEST_CASE("OptionsManager")
{
	SECTION("Set and Get Value")
	{
		OptionsManager::Instance().setValue("test.value", "test_value");
		REQUIRE(OptionsManager::Instance().getValue("test.value").compare("test_value") == 0);
	}

	SECTION("Remove a Value")
	{
		OptionsManager::Instance().removeValue("test.value");
		REQUIRE_THROWS(OptionsManager::Instance().getValue("test.value"));
		REQUIRE_THROWS(OptionsManager::Instance().getValue("test"));
	}
}

TEST_CASE("Sound")
{
	Sound* sound = AssetManager::Instance().getAsset<Sound>("./Tests/test_assets/Sound.wav");

	SECTION("Play")
	{
		REQUIRE(sound->play() == true);
	}

	SECTION("Pause")
	{
		REQUIRE(sound->pause() == true);
	}

	SECTION("Rewind")
	{
		REQUIRE(sound->rewind() == true);
	}

	SECTION("Stop")
	{
		REQUIRE(sound->stop() == true);
	}
}