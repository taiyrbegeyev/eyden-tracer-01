// Perspective Camera class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "ICamera.h"
#include <math.h>

/**
 * @brief Perspective Camera class
 */
class CCameraPerspective : public ICamera
{
public:
	/**
	 * @brief Constructor
	 * @param pos Camera origin (center of projection)
	 * @param dir Camera viewing direction
	 * @param up Up-vector
	 * @param angle (Vertical) full opening angle of the viewing frustum (in degrees)
	 * @param resolution The image resolution
	 */
	CCameraPerspective(Vec3f pos, Vec3f dir, Vec3f up, float angle, Size resolution)
		: ICamera(resolution)
		, m_pos(pos)
		, m_dir(dir)
		, m_up(up)
		, m_angle(angle)
	{
		// --- PUT YOUR CODE HERE ---
        m_aspect = (float) resolution.width / (float) resolution.height;
        m_focus = 1 / tan((Pif * angle) / 180);
        m_xAxis = normalize(dir.cross(up));
        m_yAxis = normalize(up * (-1));
	}
	virtual ~CCameraPerspective(void) = default;

	virtual bool InitRay(float x, float y, Ray& ray) override
	{
		// --- PUT YOUR CODE HERE ---
		float width = getResolution().width;
		float height = getResolution().height;

        // normalized device coordinates
        float ndcx = (x + 0.5) / width;
        float ndcy = (y + 0.5) / height;
        // screen space coordinates
        float sscx = (2 * ndcx - 1) * m_aspect;
        float sscy = 2 * ndcy - 1;

        ray.org = m_pos;
        ray.dir = normalize(sscx * m_xAxis + sscy * m_yAxis + m_focus * m_dir);
        // assign hit distance to infinity
        ray.t = std::numeric_limits<float>::max();

		return true;
	}


private:
	// input values
	Vec3f m_pos;
	Vec3f m_dir;
	Vec3f m_up;
	float m_angle;

	// preprocessed values
	float m_focus;
	Vec3f m_xAxis;
	Vec3f m_yAxis;
	Vec3f m_zAxis;
	float m_aspect;
};

