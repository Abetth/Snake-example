#ifndef Shape_h
#define Shape_h

namespace SnakeGame
{
	// ���� ��� ������������� ���������� ������
	class Shape
	{
	private:

		float xSize, ySize, zSize;                // ������
		float* diffColor, *ambiColor, *specColor; // �������
	public:
		float xCenter, yCenter, zCenter;
		Shape(float xCenter, float yCenter, float zCenter,
			float xSize, float ySize, float zSize,
			float* diffColor, float* ambiColor, float* specColor);
		virtual ~Shape() { }
		// ������� �������:
		float  getXCenter() const { return xCenter; }
		float  getYCenter() const { return yCenter; }
		float  getZCenter() const { return zCenter; }
		void   addX(double x) { xCenter += x; }
		void   addY(double y) { yCenter += y; }
		void   setXCenter(float xCenter) { this->xCenter = xCenter; }
		void   setYCenter(float yCenter) { this->yCenter = yCenter; }
		void   setZCenter(float zCenter) { this->zCenter = zCenter; }
		void   setCoords(float xCenter, float yCenter, float zCenter);
		float  getXSize() const { return xSize; }
		float  getYSize() const { return ySize; }
		float  getZSize() const { return zSize; }
		void   setXSize(float zSize) { this->xSize = xSize; }
		void   setYSize(float zSize) { this->ySize = ySize; }
		void   setZSize(float zSize) { this->zSize = zSize; }
		void   setSize(float xSize, float ySize, float zSize);
		float* getDiffColor() const { return diffColor; }
		float* getAmbiColor() const { return ambiColor; }
		float* getSpecColor() const { return specColor; }
		void   setDiffColor(float* diffColor) { this->diffColor = diffColor; }
		void   setAmbiColor(float* ambiColor) { this->ambiColor = ambiColor; }
		void   setSpecColor(float* specColor) { this->specColor = specColor; }
		void   setColors(float* diffColor, float* ambiColor, float* specColor);
		virtual void draw() = 0; // �� ������� ������� ���� ��������� � �������� ������
	};

}
#endif

