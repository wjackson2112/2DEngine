#include "Camera.hpp"

Camera::Camera()
{
	mBoundary = WindowManager::Instance().getSize(); 		//Boundary the size of the window
	mView = Rect(Point(0, 0), mBoundary);	//View is the whole window, 1.0x zoom
	mHandleRatio = Pair<float>(0.5, 0.5);					//Handle is set to the center
}

void Camera::applyBoundary()
{
	double windowRatio = WindowManager::Instance().getSize().y/WindowManager::Instance().getSize().x;
	double worldRatio = mBoundary.y / mBoundary.x;

	double scaleRatio = worldRatio / windowRatio;

	if(mView.origin().x < 0)
	{
		mView.setOrigin(Point(0.0, mView.origin().y));
	}

	if(mView.origin().y < 0)
	{
		mView.setOrigin(Point(mView.origin().x, 0.0));
	}

	if(mView.opposite().x > mBoundary.x)
	{
		mView.setOpposite(Point(mBoundary.x, mView.opposite().y));
	}

	if(mView.opposite().y > mBoundary.y)
	{
		mView.setOpposite(Point(mView.opposite().x, mBoundary.y));
	}
}

float Camera::zoom()
{
	return mBoundary.x / mView.size().x;
}

bool Camera::setBoundary(Size boundary)
{
	double aspectRatio = WindowManager::Instance().getSize().x/WindowManager::Instance().getSize().y;

	mBoundary = boundary;
	zoomTo(1);

	mUnscaledView = Rect(Point(0,0), Size(boundary.x, boundary.x / aspectRatio));

	applyBoundary();

	return true;
}

void Camera::setHandleRatio(Pair<float> handleRatio)
{
	mHandleRatio = handleRatio;
}

Point Camera::handle()
{
	double x = mView.origin().x + (mView.size().x * mHandleRatio.x);
	double y = mView.origin().y + (mView.size().y * mHandleRatio.y);

	return Point(x, y);
}

void Camera::moveHandleTo(Point handle)
{
	int x = handle.x - (mHandleRatio.x * mView.size().x);
	int y = handle.y - (mHandleRatio.y * mView.size().y);

	mView.setOrigin(Point(x,y));

	applyBoundary();
}

bool Camera::zoomTo(float zoom)
{
	Size viewSize;

	if(zoom < 1.0)
	{
		//TODO: Maybe log an error or something here?
		return false;
	}

	Point handleLoc = handle();

	viewSize = Size(mUnscaledView.size().x / zoom, mUnscaledView.size().y / zoom);
	mView.setSize(viewSize);

	moveHandleTo(handleLoc);

	applyBoundary();

	return true;
}

Rect Camera::applyTranslation(Rect input)
{
	Point origin = input.origin();
	Size size = input.size();

	origin.x -= mView.center().x - mUnscaledView.size().x/2;
	origin.y -= mView.center().y - mUnscaledView.size().y/2;

	//Apply world boundary vs camera zoom
	origin.x /= mUnscaledView.size().x/WindowManager::Instance().getSize().x;
	origin.y /= mUnscaledView.size().y/WindowManager::Instance().getSize().y;

	return Rect(origin, size);
}

Rect Camera::applyZoom(Rect input)
{
	Point origin = input.origin();
	Size size = input.size();

	origin.x = -((mView.center().x - origin.x) * zoom()) + mView.center().x;
	origin.y = -((mView.center().y - origin.y) * zoom()) + mView.center().y;

	size.x *= zoom();
	size.y *= zoom();

	//Apply world boundary vs camera zoom
	size.x /= mUnscaledView.size().x/WindowManager::Instance().getSize().x;
	size.y /= mUnscaledView.size().y/WindowManager::Instance().getSize().y;

	origin.x++;
	origin.y++;

	origin.x = floor(origin.x);
	origin.y = floor(origin.y);

	size.x = ceil(size.x);
	size.y = ceil(size.y);

	return Rect(origin, size);
}

Rect Camera::apply(Rect input)
{
	Rect output;

	output = applyZoom(input);
	output = applyTranslation(output);

	return output;
}
