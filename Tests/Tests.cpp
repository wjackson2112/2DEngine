#include "AssetManager.hpp"
#include "OptionsManager.hpp"
#include "Entity.hpp"
#include "Layer.hpp"
#include "Sound.hpp"
#include "WindowManager.hpp"
#include "EventManager.hpp"
#include "Rect.hpp"
#include "Circle.hpp"
#include "Line.hpp"
#include "Point.hpp"
#include "StateMachine.hpp"
#include "Collider.hpp"
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
		REQUIRE(WindowManager::Instance().init());
		REQUIRE(WindowManager::Instance().open());
		REQUIRE(WindowManager::Instance().close());
	}



	SECTION("Render")
	{
		REQUIRE(WindowManager::Instance().init());
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
		REQUIRE(WindowManager::Instance().init());
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

	SECTION("Line")
	{
		//Crossing lines - (X)
		Line line = Line(Point(0,0), Point(5,5));

		REQUIRE(line.a().x == 0);
		REQUIRE(line.a().y == 0);
		REQUIRE(line.b().x == 5);
		REQUIRE(line.b().y == 5);

		REQUIRE(line.contains(Point(2.5,2.5)));
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

		REQUIRE(rect.contains(Point(0,0)) == false);
		REQUIRE(rect.contains(Point(0,2)) == false);
		REQUIRE(rect.contains(Point(2,2)) == false);
		REQUIRE(rect.contains(Point(2,0)) == false);

		REQUIRE(rect.contains(Point(1,1)));
	}

	SECTION("Circle")
	{
		Circle circle = Circle(Point(5,5), 5);
		REQUIRE(circle.center().x == 5);
		REQUIRE(circle.center().y == 5);
		REQUIRE(circle.radius() == 5);

		REQUIRE(circle.contains(Point(5,5)));
		REQUIRE(circle.contains(Point(5,0)) == false);
		REQUIRE(circle.contains(Point(0,5)) == false);
		REQUIRE(circle.contains(Point(10,5)) == false);
		REQUIRE(circle.contains(Point(5,10)) == false);
		REQUIRE(circle.contains(Point(0,0)) == false);
		REQUIRE(circle.contains(Point(10,10)) == false);

		circle.setCenter(Point(10,10));
		circle.setRadius(10);

		REQUIRE(circle.center().x == 10);
		REQUIRE(circle.center().y == 10);
		REQUIRE(circle.radius() == 10);
	}

	SECTION("Intersections")
	{
		//Line vs Line
		{
			Line line1, line2;

			//Lines that cross - (X)
			line1 = Line(Point(0,0), Point(5,5));
			line2 = Line(Point(0,5), Point(5,0));
			REQUIRE(line1.intersects(line2));
			REQUIRE(line2.intersects(line1));

			//Lines that intersect and one point on one line is on the other line - (T)
			line1 = Line(Point(0,0), Point(0,5));
			line2 = Line(Point(0,2.5), Point(5,2.5));
			REQUIRE(line1.intersects(line2));
			REQUIRE(line2.intersects(line1));

			//Lines that intersect at one end - (V)
			line2 = Line(Point(0,0), Point(5,0));
			REQUIRE(line1.intersects(line2));
			REQUIRE(line2.intersects(line1));

			//Parallel lines - (||)
			line2 = Line(Point(5,0), Point(5,5));
			REQUIRE(line1.intersects(line2) == false);
			REQUIRE(line2.intersects(line1) == false);

			//Crossing lines that don't intersect - (|/)
			line2 = Line(Point(10,0), Point(5,5));
			REQUIRE(line1.intersects(line2) == false);
			REQUIRE(line2.intersects(line1) == false);

			//Lines that touch end to end (--)
			line2 = Line(Point(0,5), Point(0,10));
			REQUIRE(line1.intersects(line2));
			REQUIRE(line2.intersects(line1));
		}

		//Line vs Rect
		{
			Line line;
			Rect rect;

			rect = Rect(Point(5,5), Size(5,5));

			//Line inside the Rect
			line = Line(Point(6,6), Point(9,9));
			REQUIRE(line.intersects(rect));
			REQUIRE(rect.intersects(line));

			//Line intersects the right edge of the Rect
			line = Line(Point(7.5, 7.5), Point(12.5, 7.5));
			REQUIRE(line.intersects(rect));
			REQUIRE(rect.intersects(line));

			//Line intersects the top edge of the Rect
			line = Line(Point(7.5, 7.5), Point(7.5, 2.5));
			REQUIRE(line.intersects(rect));
			REQUIRE(rect.intersects(line));

			//Line intersects the left edge of the Rect
			line = Line(Point(7.5, 7.5), Point(2.5, 7.5));
			REQUIRE(line.intersects(rect));
			REQUIRE(rect.intersects(line));

			//Line intersects the bottom edge of the Rect
			line = Line(Point(7.5, 7.5), Point(7.5, 12.5));
			REQUIRE(line.intersects(rect));
			REQUIRE(rect.intersects(line));

			//Line does not intersect the Rect
			line = Line(Point(0,0), Point(1,1));
			REQUIRE(line.intersects(rect) == false);
			REQUIRE(rect.intersects(line) == false);

			//Line goes all the way through the Rect horizontally
			line = Line(Point(2.5, 7.5), Point(12.5, 7.5));
			REQUIRE(line.intersects(rect));
			REQUIRE(rect.intersects(line));

			//Line goes all the way through the Rect vertically
			line = Line(Point(7.5, 2.5), Point(7.5, 12.5));
			REQUIRE(line.intersects(rect));
			REQUIRE(rect.intersects(line));

			//Line goes through the left and bottom of the Rect
			line = Line(Point(7.5, 2.5), Point(12.5, 7.5));
			REQUIRE(line.intersects(rect));
			REQUIRE(rect.intersects(line));
		}

		//Line vs Circle
		{
			Line line;
			Circle circle;

			//Both points on the line are inside the circle
			line = Line(Point(4,5), Point(6,5));
			circle = Circle(Point(5,5), 5);
			REQUIRE(line.intersects(circle));
			REQUIRE(circle.intersects(line));

			//One point on the line is inside the circle
			line = Line(Point(0,0), Point(5,5));
			REQUIRE(line.intersects(circle));
			REQUIRE(circle.intersects(line));

			//The line goes through the circle
			line = Line(Point(0,0), Point(10,10));
			REQUIRE(line.intersects(circle));
			REQUIRE(circle.intersects(line));

			//The line goes through the circle, but one point is on the edge
			line = Line(Point(0,0), Point(10,5));
			REQUIRE(line.intersects(circle));
			REQUIRE(circle.intersects(line));

			//The line doesn't go through the circle, but one point is on the edge
			line = Line(Point(0,0), Point(0,5));
			REQUIRE(line.intersects(circle) == false);
			REQUIRE(circle.intersects(line) == false);

			//The line doesn't touch the circle
			line = Line(Point(0,20), Point(20,20));
			REQUIRE(line.intersects(circle) == false);
			REQUIRE(circle.intersects(line) == false);
		}

		//Rect vs Rect
		{
			Rect rect1, rect2;

			//Overlapping Rects of same size
			rect1 = Rect(Point(0,0), Size(10,10));
			rect2 = Rect(Point(5,5), Size(10,10));
			REQUIRE(rect1.intersects(rect2));
			REQUIRE(rect2.intersects(rect1));

			//Overlapping Rects that are exactly on top of one another
			rect2 = Rect(Point(0,0), Size(10,10));
			REQUIRE(rect1.intersects(rect2));
			REQUIRE(rect2.intersects(rect1));

			//Overlapping Rects where one is completely inside another
			rect2 = Rect(Point(2.5,2.5), Size(5,5));
			REQUIRE(rect1.intersects(rect2));
			REQUIRE(rect2.intersects(rect1));

			//Rects that touch only on an edge
			rect2 = Rect(Point(0,10), Size(10,10));
			REQUIRE(rect1.intersects(rect2) == false);
			REQUIRE(rect2.intersects(rect1) == false);

			//Rects that touch only at one point
			rect2 = Rect(Point(10,10), Size(10,10));
			REQUIRE(rect1.intersects(rect2) == false);
			REQUIRE(rect2.intersects(rect1) == false);

			//Rects that do not touch
			rect2 = Rect(Point(20,20), Size(10,10));
			REQUIRE(rect1.intersects(rect2) == false);
			REQUIRE(rect2.intersects(rect1) == false);
		}

		//Rect vs Circle
		{
			Rect rect;
			Circle circle;

			//Rect inside Circle
			rect = Rect(Point(4.50, 4.50), Size(1,1));
			circle = Circle(Point(5,5),5);
			REQUIRE(rect.intersects(circle));
			REQUIRE(circle.intersects(rect));

			//Circle inside Rect
			rect = Rect(Point(0,0), Size(10,10));
			circle = Circle(Point(5,5),.5);
			REQUIRE(rect.intersects(circle));
			REQUIRE(circle.intersects(rect));

			//Circle intersects Rect with circle's center in rect
			circle = Circle(Point(8,8), 5);
			REQUIRE(rect.intersects(circle));
			REQUIRE(circle.intersects(rect));

			//Circle intersects Rect with circle's center on rect
			circle = Circle(Point(10,10), 5);
			REQUIRE(rect.intersects(circle));
			REQUIRE(circle.intersects(rect));

			//Circle intersects Rect with circle's center outside rect
			circle = Circle(Point(12,12), 5);
			REQUIRE(rect.intersects(circle));
			REQUIRE(circle.intersects(rect));

			//Circle touches Rect on edge
			circle = Circle(Point(15,5), 5);
			REQUIRE(rect.intersects(circle) == false);
			REQUIRE(circle.intersects(rect) == false);

			//Circle does not intersect Rect
			circle = Circle(Point(20,20), 1);
			REQUIRE(rect.intersects(circle) == false);
			REQUIRE(circle.intersects(rect) == false);
		}

		//Circle vs Circle
		{
			Circle circle1, circle2;

			//Circle in circle
			circle1 = Circle(Point(5,5), 5);
			circle2 = Circle(Point(5,5), 2);
			REQUIRE(circle1.intersects(circle2));
			REQUIRE(circle2.intersects(circle1));

			//Circle with center in other circle
			circle2 = Circle(Point(9,5), 5);
			REQUIRE(circle1.intersects(circle2));
			REQUIRE(circle2.intersects(circle1));

			//Circle with center on other circle
			circle2 = Circle(Point(10,5), 5);
			REQUIRE(circle1.intersects(circle2));
			REQUIRE(circle2.intersects(circle1));

			//Circle with center out of other circle
			circle2 = Circle(Point(11,5), 5);
			REQUIRE(circle1.intersects(circle2));
			REQUIRE(circle2.intersects(circle1));

			//Circles touch
			circle2 = Circle(Point(15,5), 5);
			REQUIRE(circle1.intersects(circle2) == false);
			REQUIRE(circle2.intersects(circle1) == false);

			//Circles do not intersect
			circle2 = Circle(Point(20,5), 5);
			REQUIRE(circle1.intersects(circle2) == false);
			REQUIRE(circle2.intersects(circle1) == false);
		}
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

	REQUIRE(WindowManager::Instance().clear());
	REQUIRE(layer.render(&camera));
	REQUIRE(WindowManager::Instance().present());

	REQUIRE(camera.zoomTo(2));

	REQUIRE(WindowManager::Instance().clear());
	REQUIRE(layer.render(&camera));
	REQUIRE(WindowManager::Instance().present());

	camera.setHandleRatio(Pair<float>(.25, .25));
	camera.moveHandleTo(Point(320,240));

	REQUIRE(WindowManager::Instance().clear());
	REQUIRE(layer.render(&camera));
	REQUIRE(WindowManager::Instance().present());

	camera.setHandleRatio(Pair<float>(.75, .75));
	camera.moveHandleTo(Point(320,240));

	REQUIRE(WindowManager::Instance().clear());
	REQUIRE(layer.render(&camera));
	REQUIRE(WindowManager::Instance().present());

	REQUIRE(camera.zoomTo(3));

	REQUIRE(WindowManager::Instance().clear());
	REQUIRE(layer.render(&camera));
	REQUIRE(WindowManager::Instance().present());

	REQUIRE(camera.zoomTo(1));

	REQUIRE(WindowManager::Instance().clear());
	REQUIRE(layer.render(&camera));
	REQUIRE(WindowManager::Instance().present());

	REQUIRE(camera.setBoundary(Size(1280,960)));
	camera.setHandleRatio(Pair<float>(0, 0));
	// camera.moveHandleTo(Point(100, 100));

	REQUIRE(WindowManager::Instance().clear());
	REQUIRE(layer.render(&camera));
	REQUIRE(WindowManager::Instance().present());

	REQUIRE(camera.zoomTo(2));
	camera.moveHandleTo(Point(100, 100));

	REQUIRE(WindowManager::Instance().clear());
	REQUIRE(layer.render(&camera));
	REQUIRE(WindowManager::Instance().present());

	REQUIRE(WindowManager::Instance().close());
}

class CParent : public ColliderParent
{
public:
	bool calledBack;

	CParent()
	{
		reset();
	}

	void reset()
	{
		calledBack = false;
	}

	void colliderCallback(ColliderParent* collidedObject)
	{
		calledBack = true;
	}

	void negotiateCollision(ColliderParent* collidedObject)
	{

	}
};

TEST_CASE("Collider")
{
	CParent* parent = new CParent();
	Rect aRect = Rect(Point(0,0), Size(50,50));
	Rect bRect = Rect(Point(25,25), Size(50,50));

	Collider a = Collider(aRect, 100, parent);
	Collider b = Collider(bRect, 50, parent);
	REQUIRE(intersects(a,b));
	resolveCollisions(a,b);
	REQUIRE(parent->calledBack == true);
	parent->reset();

	bRect = Rect(Point(100,100), Size(50,50));
	REQUIRE(intersects(a,b) == false);
	REQUIRE(parent->calledBack == false);
	resolveCollisions(a,b);
	REQUIRE(parent->calledBack == false);

	delete parent;
}