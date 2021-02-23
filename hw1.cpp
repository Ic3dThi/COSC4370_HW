/*******************************************************
 * Homework 1: Rasterization                           *
 *-----------------------------------------------------*
 * Here you will implement the circle rasterization    *
 * method decribed in the handout.                                           *
 * To compile this in linux:                           *
 *        g++ hw1.cpp                                  *
 * Then, run the program as follows:                   *
 *        ./a.out 200                                  *
 * to generate a 200x200 image containing a circular   *
 * arc.  Note that the coordinate system we're using   *
 * places pixel centers at integer coordinates and     *
 * has the origin at the lower left.                   *
 * Your code will generate a .ppm file containing the  *
 * final image. These images can be viewed using       *
 * "display" in Linux or Irfanview in Mac/Windows.     *
 *******************************************************/

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cassert>
#include <assert.h>
using namespace std;

// We'll store image info as globals; not great programming practice
// but ok for this short program.
int radius;
bool** image;

void renderPixel(int x, int y) {
	assert(x >= 0 && y >= 0 && x <= radius && y <= radius);
	image[x][y] = 1;
	//making it symmetric messes up with the quadrant code and messes up the if statments for x2 + y2 = R2 where x ≥ 0 and x2 + y2 = R2 where y ≥ 0
	// TODO:  light up the pixel's symmetric counterpart
}
void rasterizeArc(int r)
{
	// TODO:  rasterize the arc using renderPixel to light up pixel

	//This code can only do a quadrant
	/*int x = 0;
	int y = r;
	int x0 = 2 * r;
	int y0 = 2 * r;
	int d = 1 - r;
	int dE = 3;
	int dSE = -2 * r + 5;
	renderPixel(x, y);
	while (y > x) {
		if (d < 0) {
			d += dE;
			dE += 2;
			dSE += 2;
		}
		else {

			d += dSE;
			dE += 2;
			dSE += 4;
			y--;
		}
		x++;
		renderPixel(x, y);
		*/
		//Resoure: https://www.programmersought.com/article/44255590419/
	int x = r / 2;
	int y = 0;
	int d = 0;
	int x0 = r / 2;
	int y0 = r / 2;
	while (x >= y)
	{
		//Quadrant 1
		renderPixel(x0 + x, y0 + y);
		renderPixel(x0 + y, y0 + x);
		//Quadrant 2
		renderPixel(x0 + y, y0 - x);
		renderPixel(x0 + x, y0 - y);
		//Quadrant 3
		/*
		renderPixel(x0 - x, y0 - y);
		renderPixel(x0 - y, y0 - x);
		*/
		//Quadrant 4
		renderPixel(x0 - y-50, y0 + x-50);
		renderPixel(x0 - x-50, y0 + y-50);

		//Quadrant 1
		renderPixel((x0 + x-50), (y0 + y-50));
		renderPixel((x0 + y-50), (y0 + x-50));
		//Quadrant 2


		if (d <= 0)
		{
			y++;
			d += 2 * y + 1;
		}
		if (d > 0)
		{
			x--;
			d -= 2 * x + 1;
		}
	}
}


// You shouldn't need to change anything below this point.

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "Usage: " << argv[0] << " circleSize\n";
		return 0;
	}

#ifdef _WIN32
	sscanf_s(argv[1], "%d", &radius);
#else
	sscanf(argv[1], "%d", &radius);
#endif
	if (radius <= 0) {
		cout << "Image must be of positive size.\n";
		return 0;
	}

	//Comment out this code to use arguments to select radius size
	radius = 150;

	// reserve image as 2d array
	image = new bool* [radius + 1];
	for (int i = 0; i <= radius; i++) image[i] = new bool[radius + 1];

	rasterizeArc(radius);

	char filename[50];
#ifdef _WIN32
	sprintf_s(filename, 50, "circle%d.ppm", radius);
#else
	sprintf(filename, "circle%d.ppm", radius);
#endif

	ofstream outfile(filename);
	outfile << "P3\n# " << filename << "\n";
	outfile << radius + 1 << ' ' << radius + 1 << ' ' << 1 << endl;

	for (int i = 0; i <= radius; i++)
		for (int j = 0; j <= radius; j++)
			outfile << image[radius - i][j] << " 0 0\n";

	// delete image data
	for (int i = 0; i <= radius; i++) delete[] image[i];
	delete[] image;

	return 0;
}
