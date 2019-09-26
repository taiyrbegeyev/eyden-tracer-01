#include "CameraPerspective.h"

#include "PrimSphere.h"
#include "PrimPlane.h"
#include "PrimTriangle.h"

Mat RenderFrame(ICamera& camera)
{
	// scene objects
	
	CPrimSphere s1(Vec3f(-2, 1.7f, 0), 2, RGB(1, 0, 0));
	CPrimSphere s2(Vec3f(1, -1, 1), 2.2f, RGB(0, 1, 0));
	CPrimSphere s3(Vec3f(3, 0.8f, -2), 2, RGB(0, 0, 1));
	CPrimPlane p1(Vec3f(0, -1, 0), Vec3f(0, 1, 0), RGB(1, 1, 0));
	
	CPrimTriangle t1(Vec3f(-2, 3.7f, 0), Vec3f(1, 2, 1), Vec3f(3, 2.8f, -2), RGB(0, 1, 1));
	CPrimTriangle t2(Vec3f(3, 2, 3), Vec3f(3, 2, -3), Vec3f(-3, 2, -3), RGB(1, 1, 1));
	
	Mat img(camera.getResolution(), CV_32FC3); 	// image array
	Ray ray;                            		// primary ray

	// initialize objects to work with
    std::vector<CPrim*> objects = {&s1, &s2, &s3, &p1, &t1, &t2};
	
	for(int y = 0; y< img.rows; y++)
		for (int x = 0; x < img.cols; x++) {
			
			// Initialize your ray here
			camera.InitRay(x, y, ray);
			
			Vec3f col = RGB(0, 0, 0); // background color
			
			/*
			 * Find closest intersection with scene
			 * objetcs and calculate color
			 */
			
			// Your code
			for (auto object : objects) {
			    if (object->Intersect(ray)) {
			        col = object->getColor();
			    }
			}
			
			img.at<Vec3f>(y, x) = col; // store pixel color
		}
	
	img.convertTo(img, CV_8UC3, 255);
	return img;
}

int main(int argc, char* argv[])
{
	const Size resolution(800, 600);
	// render three images with different camera settings
	
	CCameraPerspective c1(Vec3f(0, 0, 10), Vec3f(0, 0, -1), Vec3f(0, 1, 0), 60, resolution);
	Mat img1 = RenderFrame(c1);
	imwrite("perspective1.jpg", img1);
	
	CCameraPerspective c2(Vec3f(-8, 3, 8), Vec3f(1, -0.1f, -1), Vec3f(0, 1, 0), 45, resolution);
	Mat img2 = RenderFrame(c2);
	imwrite("perspective2.jpg", img2);
	
	CCameraPerspective c3(Vec3f(-8, 3, 8), Vec3f(1, -0.1f, -1), Vec3f(1, 1, 0), 45, resolution);
	Mat img3 = RenderFrame(c3);
	imwrite("perspective3.jpg", img3);
	return 0;
}
