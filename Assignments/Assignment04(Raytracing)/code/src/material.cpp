#include "world.h"
#include <glm/glm.hpp>
#include <math.h>
#include "ray.h"
#include "material.h"
#include "color.h"

Color Material::shade(const Ray& incident, const bool isSolid) const {
    Color a(0), s(0), d(0), reflectionColor(0), refractionColor(0);

    // Get the first light source in the scene
    LightSource* lightSource = world->lightSourceList[0];

    // Get surface normal, view direction, and light direction
    Vector3D normal = incident.getNormal();
    Vector3D viewDirection = incident.getDirection() * (-1);
    Vector3D lightPos = lightSource->getPosition();
    Vector3D lightDirection = unitVector(lightPos - incident.getPosition());
    Color lightIntensity = lightSource->getIntensity();

    // Calculate half vector
    Vector3D halfVec = unitVector(lightDirection + viewDirection);

    a = ka * color * lightIntensity;
    s = lightIntensity * ks * color * pow(glm::max(0.0, dotProduct(normal, halfVec)), n);
    d = lightIntensity * kd * color * (glm::max(0.0, dotProduct(normal, lightDirection)));

    // Shadow ray
    Ray shadow(incident.getPosition() + 0.01 * lightDirection, lightDirection);
    world->firstIntersection(shadow);

    if (shadow.didHit()) {
        double shadowDarkness=0.2;

        return (a + s + d*shadowDarkness);
    }



    //BEER'S APPROXIMATION
    // Calculate the distance traveled within the material
    double distance = shadow.getParameter();

    // Implement Beer's Law to simulate absorption
    Color absorption = Color(exp(-absorption_coefficient * distance));

    // Combine ambient, diffuse, and specular with absorption
    Color combinedColor = a* absorption + s* absorption + d* absorption;
    
    


    // Check if the material has reflection (kr > 0)
    if (kr > 0) {
        // Calculate reflection ray direction (use the reflected() function)
        const Vector3D reflectionDirection = reflected(incident.getDirection(), incident.getNormal());

        Ray reflectionRay(incident.getPosition() + 0.01 * reflectionDirection, reflectionDirection);

        // Apply Schlick's approximation to estimate the reflection coefficient
        double r0 = ((1 - eta) / (1 + eta)) * ((1 - eta) / (1 + eta));
        double cosine = dotProduct(-incident.getDirection(), incident.getNormal());
        double reflectionCoefficient = r0 + (1 - r0) * pow(1 - cosine, 5);

        // Recursive ray tracing for reflection with the estimated reflection coefficient
        reflectionColor = world->traceRay(reflectionRay, incident.getLevel() + 1) * reflectionCoefficient;
    }

   
// Check if the material has refraction (kt > 0)
if (kt > 0) {
    Vector3D refractionDirection;
    double n1, n2;  // Refractive indices of the two media

    // Determine the refractive indices based on the direction of the ray (incoming or outgoing)
    if (dotProduct(incident.getDirection(), incident.getNormal()) > 0) {
        // Ray is exiting the material (incident and normal in opposite directions)
        n1 = eta;  // Refractive index of the current medium
        n2 = 1.0;  // Refractive index of the outer medium (usually air)
    } else {
        // Ray is entering the material (incident and normal in the same direction)
        n1 = 1.0;  // Refractive index of the outer medium (usually air)
        n2 = eta;  // Refractive index of the material
    }

    // Calculate the refracted ray direction (use Snell's law)
    double n = n1 / n2;
    double cosI = -dotProduct(incident.getDirection(), incident.getNormal());
    double sinT2 = n * n * (1.0 - cosI * cosI);

    // Check for total internal reflection
    if (sinT2 <= 1.0) {
        double cosT = sqrt(1.0 - sinT2);
        refractionDirection = n * incident.getDirection() + (n * cosI - cosT) * incident.getNormal();
        Ray refractionRay(incident.getPosition() + 0.01 * refractionDirection, refractionDirection);

        // Recursive ray tracing for refraction
        refractionColor = world->traceRay(refractionRay, incident.getLevel() + 1);

        // Attenuate the refraction with the refraction coefficient kt
        refractionColor = refractionColor * kt;
    } else {
        // Total internal reflection, handle it by treating it as reflection
        Vector3D reflectionDirection = reflected(incident.getDirection(), incident.getNormal());
        Ray reflectionRay(incident.getPosition() + 0.01 * reflectionDirection, reflectionDirection);

        // Recursive ray tracing for reflection (use reflectionColor here)
        reflectionColor = world->traceRay(reflectionRay, incident.getLevel() + 1);

        // Attenuate the reflection with the reflection coefficient kr
        reflectionColor = reflectionColor * kr;
    }
}


// Combine ambient, diffuse, specular, reflection, and refraction
Color finalColor = combinedColor + reflectionColor + refractionColor;

return finalColor;

}