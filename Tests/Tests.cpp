#include "AssetManager.hpp"
#include "OptionsManager.hpp"
#include "Sprite.hpp"
#include "Sound.hpp"
#include "WindowManager.hpp"
#include "EventManager.hpp"
#include "Rect.hpp"
#include "Point.hpp"
#include "StateMachine.hpp"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

/* Asset Manager */

TEST_CASE("AssetManager")
{
	SECTION("Get a Sound")
	{
		Sound* sound = AssetManager::Instance().getAsset<Sound*>("./Tests/test_assets/Sound.wav");
		REQUIRE(sound != NULL);
		REQUIRE(sound->hasError() == false);
	}
}

TEST_CASE("Sound")
{
	Sound* sound = AssetManager::Instance().getAsset<Sound*>("./Tests/test_assets/Sound.wav");

	SECTION("Get")
	{
		REQUIRE(sound != NULL);
	}
	
	SECTION("Play")
	{
		REQUIRE(sound->play(0) == true);
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

TEST_CASE("WindowManager")
{
	SECTION("Init")
	{
		REQUIRE(WindowManager::Instance().init() == true);
		WindowManager::Instance().close();
	}

	SECTION("Open")
	{
		REQUIRE(WindowManager::Instance().open() == true);
		WindowManager::Instance().close();
	}

	SECTION("Render")
	{
		REQUIRE(WindowManager::Instance().open() == true);
		Sprite sprite = AssetManager::Instance().getAsset<Sprite>("./Tests/test_assets/Ball.png");
		sprite.scaleToWidth(30);
		WindowManager::Instance().clear();
		sprite.render();
		WindowManager::Instance().present();
		WindowManager::Instance().close();	
	}

	SECTION("Name")
	{
		REQUIRE(WindowManager::Instance().init() == true);
		REQUIRE(WindowManager::Instance().setName("Test"));
		REQUIRE(WindowManager::Instance().open() == true);
		WindowManager::Instance().close();
	}

	SECTION("Size")
	{
		REQUIRE(WindowManager::Instance().init() == true);
		REQUIRE(WindowManager::Instance().setSize(800, 600));
		REQUIRE(WindowManager::Instance().open() == true);
		WindowManager::Instance().close();
	}

	SECTION("Renderer")
	{
		REQUIRE(WindowManager::Instance().open() == true);
		REQUIRE(WindowManager::Instance().renderer != NULL);
		WindowManager::Instance().close();
	}

	SECTION("Full")
	{
		REQUIRE(WindowManager::Instance().init() == true);
		REQUIRE(WindowManager::Instance().setFull(true));
		REQUIRE(WindowManager::Instance().open() == true);
		WindowManager::Instance().close();
	}
}

TEST_CASE("EventManager")
{
	class TestHandler : public IGameEventHandler
	{
		void handleGameEvents(vector<int> events)
		{
			if(events[0] == 0)
			{
				eventOccured = false;
			} 
			else 
			{
				eventOccured = true;
			}
		}

	public:
		bool eventOccured = false;
	};

	EventManager* eventManager = new EventManager(1);
	TestHandler* testHandler = new TestHandler();

	SECTION("Construct")
	{
		REQUIRE(eventManager != NULL);
	}

	SECTION("Report")
	{
		eventManager->registerGameEventHandler(testHandler);
		eventManager->handleGameEvents();
		REQUIRE(testHandler->eventOccured == false);
		eventManager->reportGameEvent(0);
		eventManager->handleGameEvents();
		REQUIRE(testHandler->eventOccured == true);
		eventManager->handleGameEvents();
		REQUIRE(testHandler->eventOccured == false);
	}
}

TEST_CASE("Primitives")
{
	SECTION("Pair")
	{
		Pair<string> pair = Pair<string>("One", "Two");
		REQUIRE(pair.x == "One");
		REQUIRE(pair.y == "Two");
	}

	SECTION("Point")
	{
		Point point = Point(5.5, 10.5);
		REQUIRE(point.x == 5.5);
		REQUIRE(point.y == 10.5);
	}

	SECTION("Size")
	{
		Size size = Size(2, 5);
		REQUIRE(size.x == 2);
		REQUIRE(size.y == 5);
	}

	SECTION("Rect")
	{
		Rect rect = Rect(Point(2.5,4.5), Size(5,9));
		
		REQUIRE(rect.origin().x == 2.5);
		REQUIRE(rect.origin().y == 4.5);
		REQUIRE(rect.size().x 	== 5);
		REQUIRE(rect.size().y 	== 9);

		rect.setOrigin(Point(1.5, 3.5));
		rect.setSize(Size(4, 8));
		REQUIRE(rect.origin().x 	== 1.5 );
		REQUIRE(rect.origin().y 	== 3.5 );
		REQUIRE(rect.size().x 		== 4   );
		REQUIRE(rect.size().y 		== 8   );
		REQUIRE(rect.center().x 	== 3.5 );
		REQUIRE(rect.center().y 	== 7.5 );
		REQUIRE(rect.opposite().x 	== 5.5 );
		REQUIRE(rect.opposite().y 	== 11.5);

		rect.setCenter(Point(1, 1));
		rect.setSize(Size(2, 2), CENTER);
		REQUIRE(rect.origin().x 	== 0);
		REQUIRE(rect.origin().y 	== 0);
		REQUIRE(rect.size().x 		== 2);
		REQUIRE(rect.size().y 		== 2);
		REQUIRE(rect.center().x 	== 1);
		REQUIRE(rect.center().y 	== 1);
		REQUIRE(rect.opposite().x 	== 2);
		REQUIRE(rect.opposite().y 	== 2);

		REQUIRE(rect.contains(Point(0,0)));
		REQUIRE(rect.contains(Point(0,2)));
		REQUIRE(rect.contains(Point(2,2)));
		REQUIRE(rect.contains(Point(2,0)));

		REQUIRE(rect.contains(Point(1,1)));
	}
}

typedef enum
{
	IDLE,
	DONE
} States;

bool called = false;
void callback(States prev, States curr)
{
	called = true;
}

TEST_CASE("State Machine")
{
	StateMachine<States> machine = StateMachine<States>(callback, IDLE);
	
	REQUIRE(machine.getState() == IDLE);
	machine.updateState(DONE);
	REQUIRE(machine.getState() == DONE);
	REQUIRE(called == true);
}