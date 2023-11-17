#include "world.h"
#include "color.h"
#include "ray.h"

using namespace std;

float World::firstIntersection(Ray& ray)
{
    for (int i = 0; i < objectList.size(); i++)
        objectList[i]->intersect(ray);
    return ray.getParameter();
}

Color World::shade_ray(Ray& ray)
{
    firstIntersection(ray);
    if (ray.didHit())
        return (ray.intersected())->shade(ray);
    return background;
}

Color World::traceRay(Ray& ray, int recursionLevel) {
    if (recursionLevel >= 10) {
        // Maximum recursion depth reached, return background color
        return background;
    }

    firstIntersection(ray);

    if (ray.didHit()) {
        const Object* hitObject = ray.intersected();
        Color objectColor = hitObject->shade(ray);

        // Handle reflection (if kr > 0)
        if (hitObject->getMaterial()->kr > 0) {
            // Calculate reflected ray
            Vector3D reflectionDirection = reflected(ray.getDirection(), ray.getNormal());
            Ray reflectionRay(ray.getPosition() + 0.01 * reflectionDirection, reflectionDirection);

            // Recursive call for reflection
            Color reflectionColor = traceRay(reflectionRay, recursionLevel + 1);

            // Combine object color and reflection color with reflection coefficient
            objectColor = objectColor + (hitObject->getMaterial()->kr * reflectionColor);
        }

        // Handle refraction (if kt > 0)
        if (hitObject->getMaterial()->kt > 0) {
            // Calculate the refracted ray using Snell's law
            Vector3D normal = ray.getNormal(); // Surface normal at the point of intersection
            double n1 = 1.0; // Refractive index of the current medium (e.g., air)
            double n2 = hitObject->getMaterial()->eta; // Refractive index of the material

            double cosI = -dotProduct(normal, ray.getDirection());
            double etaRatio = n1 / n2;
            double k = 1.0 - etaRatio * etaRatio * (1.0 - cosI * cosI);

            Vector3D refractedDirection;
            if (k >= 0) {
                refractedDirection = etaRatio * ray.getDirection() + (etaRatio * cosI - sqrt(k)) * normal;
                Ray refractionRay(ray.getPosition() - 0.01 * normal, refractedDirection);

                // Recursive call for refraction
                Color refractionColor = traceRay(refractionRay, recursionLevel + 1);

                // Combine object color and refraction color with refraction coefficient
                objectColor = objectColor + (hitObject->getMaterial()->kt * refractionColor);
            }
        }

        return objectColor;
    }

    return background;
}
