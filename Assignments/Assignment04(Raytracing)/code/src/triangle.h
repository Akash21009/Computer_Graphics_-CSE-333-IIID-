#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "object.h"
#include "ray.h"
#include "vector3D.h"
#include "color.h"

class Triangle : public Object {
private:
    Vector3D vertex0;
    Vector3D vertex1;
    Vector3D vertex2;

public:
    Triangle(const Vector3D& v0, const Vector3D& v1, const Vector3D& v2, Material* material);

    virtual bool intersect(Ray& ray) const;
};

#endif
