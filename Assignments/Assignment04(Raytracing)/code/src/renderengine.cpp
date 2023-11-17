#include "renderengine.h"

const Color RenderEngine::trace(const int i, const int j)
{
	Vector3D ray_dir = camera->get_ray_direction(i, j);
	Ray ray(camera->get_position(), ray_dir);
	return world->shade_ray(ray);
}

bool RenderEngine::renderLoop()
{
	static int i = 0;
	for(int j = 0; j<camera->getHeight(); j++)
	{
		Color color = trace(i, j);
		color.clamp();
		camera->drawPixel(i, j, color);
	}

	if(++i == camera->getWidth())
	{
		i = 0;
		return true;
	}
	return false;
}
