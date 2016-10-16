#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <iostream>

#include "Rect.hpp"
#include "Point.hpp"
#include "WindowManager.hpp"

class Camera
{
	Size  		mBoundary;
	Rect 		mView;
	Pair<float> mHandleRatio;

	void applyBoundary();
	Rect applyZoom(Rect input);
	Rect applyTranslation(Rect input); 
	float zoom();
	Point handle();

public:
	Camera();

	void setBoundary(Size boundary);
	void setHandleRatio(Pair<float> handleRatio);

	void moveHandleTo(Point handle);
	void zoomTo(float zoom);

	Rect apply(Rect input);
};

#endif