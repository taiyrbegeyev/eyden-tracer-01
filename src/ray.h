// Basic ray structure
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "../include/types.h"

/// Basic ray structure
struct Ray
{
	Vec3f	org;		///< Origin
	Vec3f	dir;		///< Direction
	float	t;			///< Current/maximum hit distance
};
