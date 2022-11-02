#ifndef Body_h
#define Body_h

#include "shape.h"

namespace SnakeGame
{
	class Body : public Shape
	{
	public:
		Body(float xCenter, float yCenter, float zCenter,
			float xSize, float ySize, float zSize,
			float* diffColor, float* ambiColor, float* specColor)
			: Shape(xCenter, yCenter, zCenter,
				xSize, ySize, zSize,
				specColor, diffColor, ambiColor) { }
		virtual void draw();
	};

}
#endif

