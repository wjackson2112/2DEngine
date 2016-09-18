
#include "AssetManager.hpp"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

/* Asset Manager */
TEST_CASE("AssetManagerExists")
{
	AssetManager* manager = AssetManager::Instance();
	REQUIRE(AssetManager::Instance() != NULL);
}