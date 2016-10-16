#include <algorithm>
#include "Entity.hpp"
#include "Layer.hpp"

using namespace std;

Layer::~Layer()
{
	clear();
}

void Layer::render(Camera* camera)
{
	for(auto &entity : entities)
	{
		entity.render(camera);
	}
}
void Layer::update(int frameTime)
{
	for(auto &entity : entities)
	{
		entity.update(frameTime);
	}
}

void Layer::add(Entity entity)
{
	entities.push_back(entity);
}
void Layer::remove(Entity entity)
{
	entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
}
void Layer::clear()
{
	entities.clear();
}