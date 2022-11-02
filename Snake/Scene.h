#ifndef Scene_h
#define Scene_h
#include "Apple.h"
#include "Body.h"
#include "Shape.h"
#include <vector>

namespace SnakeGame
{

    class Scene
    {
        Shape* walls[5];
        Shape* shapes[20];
        int button;           // ������ ���� (-1 - �� ���������, 0 - ���, 2 - �����)

        float angleX, angleY; // �������� ��� �������� ����� 
        float mouseX, mouseY; // ������ ����������
        float width, height;  // ������ ����
        float distZ;          // ������� �� �� Z �� �����
        bool finish;          // ������ ����, �� ��� ���������
        float xStep, zStep;   // ������� �� �������� ���������
        int time;             // �������� ��� � ��������
                              
        int xFrom, zFrom;     // ������� �������, � ����� ���������� �����������
        int xTo, zTo;         // ������� �������, ���� ���������� �����������
    public:
        int objects = 0;
        double arr[30][2];
        int num = 0;
        int motionNum;
        Body* body[30];
        Apple* apple;
        Scene();
        ~Scene();
        bool checkCollision(int x1, int y1, int x2, int y2);
        void deleteBody();
        void moveApple();
        void motion();
        void on_paint();
        void addBody();
        void on_size(int width, int height);
        void on_mouse(int button, int state, int x, int y);
        void on_motion(int x, int y);
        void on_special(int key, int x, int y);
        void on_timer(int value);
        void mainmotion(int value);
        void collision();
    private:
        void initialize();
    };

}
#endif
