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
        int button;           // кнопка миші (-1 - не натиснута, 0 - ліва, 2 - права)

        float angleX, angleY; // поточний кут повороту сцени 
        float mouseX, mouseY; // поточні координати
        float width, height;  // Розміри вікна
        float distZ;          // відстань по осі Z до сцени
        bool finish;          // ознака того, що гру завершено
        float xStep, zStep;   // відстань між окремими стрижнями
        int time;             // поточний час у секуднах
                              
        int xFrom, zFrom;     // індекси стрижня, з якого починається пересування
        int xTo, zTo;         // індекси стрижня, яким закінчується пересування
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
