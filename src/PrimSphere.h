// Sphere Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

/**
 * @brief Sphere Geaometrical Primitive class
 */
class CPrimSphere : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param center Position of the center of the sphere
	 * @param radius Radius of the sphere
	 */
	CPrimSphere(Vec3f center, float radius, Vec3f color)
		: CPrim(color)
		, m_center(center)
		, m_radius(radius)
	{}
	virtual ~CPrimSphere(void) = default;

	virtual bool Intersect(Ray &ray) override
	{
		// --- PUT YOUR CODE HERE ---
		float a = ray.dir.dot(ray.dir);
        float b = 2 * ray.dir.dot(ray.org - m_center);
        float c = (ray.org - m_center).dot(ray.org - m_center) - m_radius * m_radius;

        // find discriminant
        float D = b * b - 4 * a * c;
        if (D < 0) {
            return false;
        }

        // find roots of the quadratic equation
        float t1 = ((-b) + sqrt(D)) / 2 * a;
        float t2 = ((-b) - sqrt(D)) / 2 * a;

        if ((t1 < Epsilon && t2 < Epsilon) || (t1 > ray.t && t2 > ray.t)) {
            return false;
        }

        // find the smallest value aka shortest one
        if (t1 < t2) {
            ray.t = t1;
        }
        else {
            ray.t = t2;
        }

        return true;
	}
	
	
private:
	Vec3f m_center;	///< Position of the center of the sphere
	float m_radius;	///< Radius of the sphere
};

