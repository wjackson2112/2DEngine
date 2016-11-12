#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include <iostream>
#include "Entity.hpp"
#include "Camera.hpp"

using namespace std;

class Layer
{
private:
	vector<Entity*> entities;

public:
	~Layer();

	bool render(Camera* camera);
	void update(int frameTime);

	void add(Entity* entity);
	void remove(Entity* entity);
	void clear();
};

#endif