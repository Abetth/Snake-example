#ifndef Scene_h
#define Scene_h
#include "Apple.h"
#include "Body.h"
#include "Shape.h"
#include <vector>

namespace SnakeGame
{

	const int M = 3, N = 3;
	class Scene
	{

		Shape* shapes[20];
		int button;           // кнопка миші (-1 - не натиснута, 0 - ліва, 2 - права)

		float angleX, angleY; // поточний кут повороту сцени 
		float mouseX, mouseY; // поточні координати
		float width, height;  // Розміри вікна
		float distZ;          // відстань по осі Z до сцени
		int   record;     // Кращий результат у грі (сек)
		bool finish;          // ознака того, що гру завершено
		bool showResult;       // ознака показу кращого результату
		float xStep, zStep;
		int time;             // поточний час у секуднах
		int fields[M][N];
		int xFrom, zFrom;
		int xTo, zTo;
	public:
		int objects = 0;
		double arr[30][2];
		int num = 0;
		int motionNum;
		Body* body[10];
		Apple* apple;
		Scene(float xStep, float zStep);
		~Scene();
		void moveApple();
		void motion();
		void on_paint();
		void addBody();
		void deleteShapes();
		void resetView();
		void on_size(int width, int height);
		void on_mouse(int button, int state, int x, int y);
		void on_special(unsigned char key, int x, int y);
		void on_timer(int value);
		void mainmotion(int value);
		void collision();
	private:
		void initialize();
	};

}
#endif
