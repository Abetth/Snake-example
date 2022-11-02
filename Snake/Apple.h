#ifndef Apple_h
#define Apple_h

#include "shape.h"

namespace SnakeGame
{
    class Apple : public Shape
    {
    public:
        Apple(float xCenter, float yCenter, float zCenter,
            float xSize, float ySize, float zSize,
            float* diffColor, float* ambiColor, float* specColor)
            : Shape(xCenter, yCenter, zCenter,
                xSize, ySize, zSize,
                specColor, diffColor, ambiColor) { }
        virtual void draw();
    };

}
#endif

