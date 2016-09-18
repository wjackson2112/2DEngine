
#include "AssetManager.hpp"
#include "OptionsManager.hpp"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

/* Asset Manager */
TEST_CASE("AssetManagerExists")
{
	REQUIRE(AssetManager::Instance() != NULL);
}

/* Options Manager */
TEST_CASE("OptionsManagerExists")
{
	REQUIRE(OptionsManager::Instance() != NULL);
}