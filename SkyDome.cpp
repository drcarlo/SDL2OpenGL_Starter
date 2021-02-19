#include "SkyDome.h"

Skydome::Skydome()
{

	/*
	float elevationStep = pi / (float)(resolution - 1);
	float horizontalStep = (2.0f * pi) / (float)(resolution - 1);


	float x, y, z, u, v;
	for (int longitude = 0; longitude < resolution + 1; longitude++) {
		for (int latitude = 0; latitude < resolution + 1; latitude++) {


			float theta = (pi / 2) - (longitude * elevationStep);
			float phi = latitude * horizontalStep;

			y = radius * sinf(theta);
			x = (radius * cosf(theta)) * cosf(phi);
			z = (radius * cosf(theta)) * sinf(phi);

			u = (float)latitude / (float)resolution;
			v = (float)(longitude) / (float)resolution;

		}
	}



	unsigned int c, n;
	for (int latitude = 0; latitude < resolution; latitude++) {

		c = latitude * (resolution + 1);
		n = c + resolution + 1;

		for (int longitude = 0; longitude < resolution; longitude++) {
			if (longitude != 0) {


			}
			if (longitude != resolution - 1) {


			}
			n++;
			c++;
		}
	}

	*/

}
