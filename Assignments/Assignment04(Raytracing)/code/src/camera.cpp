#include "camera.h"
#define _USE_MATH_DEFINES
#include <cmath>

Camera::Camera(const Vector3D& _pos, const Vector3D& _target, const Vector3D& _up, float _fovy, int _width, int _height) : 
position(_pos), target(_target), up(_up), fovy(_fovy), width(_width), height(_height)
{
	up.normalize();

	line_of_sight = target - position;

	//Calculate the camera basis vectors
	//Camera looks down the -w axis
	w = -line_of_sight;
	w.normalize();
	u = crossProduct(up, w);
	u.normalize();
	v = crossProduct(w, u);
	v.normalize();
	bitmap  = new unsigned char[width * height * 3]; //RGB
	for (std::size_t i = 0; i < 3*width*height; ++i) {
		bitmap[i] = 0;
	}
	focalHeight = 1.0; //Let's keep this fixed to 1.0
	aspect = float(width)/float(height);
	focalWidth = focalHeight * aspect; //Height * Aspect ratio
	focalDistance = focalHeight/(2.0 * tan(fovy * M_PI/(180.0 * 2.0))); //More the fovy, close is focal plane
}

Camera::~Camera()
{
	delete []bitmap;
}

//Get direction of viewing ray from pixel coordinates (i, j)
const Vector3D Camera::get_ray_direction(const int i, const int j) const
{
	Vector3D dir(0.0, 0.0, 0.0);
	dir += -w * focalDistance;
	float xw = aspect*(i - width/2.0 + 0.5)/width;
	float yw = (j - height/2.0 + 0.5)/height;
	dir += u * xw;
	dir += v * yw;

	dir.normalize();
	return dir;
}

void Camera::drawPixel(int i, int j, Color c)
{
	int index = (i + j*width)*3;
	bitmap[index + 0] = 255 * c.r ;
	bitmap[index + 1] = 255 * c.g;
	bitmap[index + 2] = 255 * c.b;
}
