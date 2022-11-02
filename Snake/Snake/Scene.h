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
		int button;           // ������ ���� (-1 - �� ���������, 0 - ���, 2 - �����)

		float angleX, angleY; // �������� ��� �������� ����� 
		float mouseX, mouseY; // ������ ����������
		float width, height;  // ������ ����
		float distZ;          // ������� �� �� Z �� �����
		int   record;     // ������ ��������� � �� (���)
		bool finish;          // ������ ����, �� ��� ���������
		bool showResult;       // ������ ������ ������� ����������
		float xStep, zStep;
		int time;             // �������� ��� � ��������
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
