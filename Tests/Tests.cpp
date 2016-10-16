#include "AssetManager.hpp"
#include "OptionsManager.hpp"
#include "Entity.hpp"
#include "Layer.hpp"
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
		REQUIRE(sound->play(0));
	}

	SECTION("Pause")
	{
		REQUIRE(sound->pause());
	}

	SECTION("Rewind")
	{
		REQUIRE(sound->rewind());
	}

	SECTION("Stop")
	{
		REQUIRE(sound->stop());
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
		REQUIRE(WindowManager::Instance().init());
		REQUIRE(WindowManager::Instance().close());
	}

	SECTION("Open")
	{
		REQUIRE(WindowManager::Instance().open());
		REQUIRE(WindowManager::Instance().close());
	}

	SECTION("Render")
	{
		REQUIRE(WindowManager::Instance().open());
		REQUIRE(WindowManager::Instance().clear());
		REQUIRE(WindowManager::Instance().present());
		REQUIRE(WindowManager::Instance().close());
	}

	SECTION("Name")
	{
		REQUIRE(WindowManager::Instance().init());
		REQUIRE(WindowManager::Instance().setName("Test"));
		REQUIRE(WindowManager::Instance().open());
		REQUIRE(WindowManager::Instance().close());
	}

	SECTION("Size")
	{
		REQUIRE(WindowManager::Instance().init());
		REQUIRE(WindowManager::Instance().setSize(Size(800, 600)));
		REQUIRE(WindowManager::Instance().open());
		REQUIRE(WindowManager::Instance().close());
	}

	SECTION("Renderer")
	{
		REQUIRE(WindowManager::Instance().open());
		REQUIRE(WindowManager::Instance().renderer != NULL);
		REQUIRE(WindowManager::Instance().close());
	}

	SECTION("Full")
	{
		REQUIRE(WindowManager::Instance().init());
		REQUIRE(WindowManager::Instance().setFull(true));
		REQUIRE(WindowManager::Instance().open());
		REQUIRE(WindowManager::Instance().close());
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
} State;

bool called = false;
State p, c;
void callback(State prev, State curr)
{
	called = true;
	p = prev;
	c = curr;
}

TEST_CASE("State Machine")
{
	StateMachine<State> machine = StateMachine<State>(callback, IDLE);

	REQUIRE(machine.getState() == IDLE);
	machine.updateState(DONE);
	REQUIRE(machine.getState() == DONE);
	REQUIRE(called == true);
	REQUIRE(p == IDLE);
	REQUIRE(c == DONE);
}

TEST_CASE("Sprite")
{
	REQUIRE(WindowManager::Instance().init());
	REQUIRE(WindowManager::Instance().open());

	Sprite sprite = AssetManager::Instance().getAsset<Sprite>("./Tests/test_assets/Ball.png");
	Rect renderLocation = Rect(Point(25,25), Size(25,50));

	REQUIRE(WindowManager::Instance().clear());
	REQUIRE(sprite.render(renderLocation));
	REQUIRE(WindowManager::Instance().present());
	REQUIRE(WindowManager::Instance().close());
}

TEST_CASE("Entity")
{
	Entity entity;

	REQUIRE(WindowManager::Instance().init());
	REQUIRE(WindowManager::Instance().open());

	entity = Entity("./Tests/test_assets/Ball.png");

	REQUIRE(WindowManager::Instance().clear());
	REQUIRE(entity.render(NULL));
	REQUIRE(WindowManager::Instance().present());

	entity.update(1);

	REQUIRE(WindowManager::Instance().clear());
	REQUIRE(entity.render(NULL));
	REQUIRE(WindowManager::Instance().present());

	REQUIRE(WindowManager::Instance().close());
}

TEST_CASE("Layer")
{
	REQUIRE(WindowManager::Instance().init());
	REQUIRE(WindowManager::Instance().open());

	Entity entity1 = Entity("./Tests/test_assets/Ball.png");
	entity1.setOrigin(Point(0,0));
	entity1.setSize(Size(25,25));

	Entity entity2 = Entity("./Tests/test_assets/Ball.png");
	entity2.setOrigin(Point(25,25));
	entity2.setSize(Size(50,50));

	Layer layer1 = Layer();
	Layer layer2 = Layer();
	layer1.add(entity1);
	layer2.add(entity2);

	REQUIRE(WindowManager::Instance().clear());
	REQUIRE(layer1.render(NULL));
	REQUIRE(layer2.render(NULL));
	REQUIRE(WindowManager::Instance().present());

	layer1.update(1);
	layer2.update(1);

	REQUIRE(WindowManager::Instance().clear());
	REQUIRE(layer1.render(NULL));
	REQUIRE(WindowManager::Instance().present());

	REQUIRE(WindowManager::Instance().clear());
	REQUIRE(layer2.render(NULL));
	REQUIRE(WindowManager::Instance().present());

	REQUIRE(WindowManager::Instance().close());
}

TEST_CASE("Camera")
{
	REQUIRE(WindowManager::Instance().init() == true);
	REQUIRE(WindowManager::Instance().open() == true);

	Entity entity1 = Entity("./Tests/test_assets/Ball.png");
	entity1.setSize(Size(50,50));
	entity1.setCenter(Point(320,240));

	Entity entity2 = Entity("./Tests/test_assets/Ball.png");
	entity2.setSize(Size(50,50));
	entity2.setOrigin(Point(entity1.origin().x - 50,entity1.origin().y - 50));

	Entity entity3 = Entity("./Tests/test_assets/Ball.png");
	entity3.setSize(Size(50,50));
	entity3.setOrigin(Point(entity1.origin().x + 50,entity1.origin().y + 50));

	Entity entity4 = Entity("./Tests/test_assets/Ball.png");
	entity4.setSize(Size(50,50));
	entity4.setOrigin(Point(entity1.origin().x - 50,entity1.origin().y + 50));

	Entity entity5 = Entity("./Tests/test_assets/Ball.png");
	entity5.setSize(Size(50,50));
	entity5.setOrigin(Point(entity1.origin().x + 50,entity1.origin().y - 50));

	Layer layer = Layer();
	layer.add(entity1);
	layer.add(entity2);
	layer.add(entity3);
	layer.add(entity4);
	layer.add(entity5);

	Camera camera = Camera();

	REQUIRE(WindowManager::Instance().clear());
	REQUIRE(WindowManager::Instance().present());

	sleep(1);

	REQUIRE(WindowManager::Instance().clear());
	REQUIRE(layer.render(&camera));
	REQUIRE(WindowManager::Instance().present());

	sleep(1);

	REQUIRE(camera.zoomTo(2));

	REQUIRE(WindowManager::Instance().clear());
	REQUIRE(layer.render(&camera));
	REQUIRE(WindowManager::Instance().present());

	sleep(1);

	camera.setHandleRatio(Pair<float>(.25, .25));
	camera.moveHandleTo(Point(320,240));

	REQUIRE(WindowManager::Instance().clear());
	REQUIRE(layer.render(&camera));
	REQUIRE(WindowManager::Instance().present());

	sleep(1);

	camera.setHandleRatio(Pair<float>(.75, .75));
	camera.moveHandleTo(Point(320,240));

	REQUIRE(WindowManager::Instance().clear());
	REQUIRE(layer.render(&camera));
	REQUIRE(WindowManager::Instance().present());

	sleep(1);

	REQUIRE(camera.zoomTo(3));

	REQUIRE(WindowManager::Instance().clear());
	REQUIRE(layer.render(&camera));
	REQUIRE(WindowManager::Instance().present());

	sleep(1);

	REQUIRE(camera.zoomTo(1));

	REQUIRE(WindowManager::Instance().clear());
	REQUIRE(layer.render(&camera));
	REQUIRE(WindowManager::Instance().present());

	sleep(1);

	REQUIRE(camera.setBoundary(Size(1280,960)));
	camera.setHandleRatio(Pair<float>(0, 0));
	// camera.moveHandleTo(Point(100, 100));

	REQUIRE(WindowManager::Instance().clear());
	REQUIRE(layer.render(&camera));
	REQUIRE(WindowManager::Instance().present());

	sleep(1);

	REQUIRE(camera.zoomTo(2));
	camera.moveHandleTo(Point(100, 100));

	REQUIRE(WindowManager::Instance().clear());
	REQUIRE(layer.render(&camera));
	REQUIRE(WindowManager::Instance().present());

	REQUIRE(WindowManager::Instance().close());
}