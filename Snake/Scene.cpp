#define _CRT_SECURE_NO_WARNINGS
#define DEBUG
#include <iostream>
#include <ctime>
#include <gl/glut.h>
#include <stdio.h>
#include "Scene.h"
#include "utils.h"
#include "Apple.h"



namespace SnakeGame
{
    using namespace GraphUtils;

    // ��������� ������������ - ������� �� �������� ���������:
    Scene::Scene()
    {
        walls[0] = new Body(0, 1, -0.06, 3.05, 0.05, 0.2, diffGray, ambiGray, specYellow);
        walls[1] = new Body(0, -1.1, -0.06, 3.05, 0.05, 0.2, diffGray, ambiGray, specYellow);
        walls[2] = new Body(-1.5, -0.075, -0.06, 0.05, 2.1, 0.2, diffGray, ambiGray, specYellow);
        walls[3] = new Body(1.5, -0.075, -0.06, 0.05, 2.1, 0.2, diffGray, ambiGray, specYellow);
        walls[4] = new Body(0, -0.05, -0.1, 3, 2.1, 0.1, diffBlue, ambiBlue, specBlue);

        motionNum = 0;
        apple = new Apple(1, 0, 0, 0.05, 0.05, 0.05, diffYellow, ambiYellow, specRed);
        shapes[objects] = apple;
        objects++;

        body[0] = new Body(0, 0, 0, 0.1, 0.1, 0.1, diffGreen, ambiGreen, specGreen);

        initialize();
    }

    Scene::~Scene()
    {
        // ��������� �� ������:
        for (int i = 0; i < objects; i++)
        {
            delete shapes[i];
        }
    }

    void Scene::deleteBody() {
        for (int i = num; i > 0; i--) {
            if (body[i]) {
                delete body[i];
            }
        }

        num = 0;
    }

    // ����������� ����� (���������� ��������, � ���� � ������ ���������� ���):
    void Scene::initialize()
    {
        deleteBody();


        body[0]->setCoords(0, 0, 0);
        motionNum = 0;

        distZ = -3;
        angleX = 0;
        angleY = 0;
        time = 0;
        finish = false;
    }

    
    // ���������� ��䳿, ���'����� � �������������� ����
    void Scene::on_paint()
    {
        char text[128]; // ����� �������, 
                        // ���������� ������ ������� �������� �� ����� ���:
        if (finish)
        {
            sprintf(text, "Game over. Time: %d sec.   F2 - Restart game   Esc - Exit", time);
        }
        else
        {
            sprintf(text, "F2 - Restart game   Esc - Exit              Time: %d sec.", time);
        }
        // ������������ ������� ��������� ����, ��� ���� �������� ��� ����:
        glViewport(0, 0, width, height);

        // ���������� ��������� �������� � ������� �����:
        float lightAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // ���� �������� ��������� 
        float lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // ���� ��������� ��������� 
        float lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };// ���� ������������ �����������
        float lightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f };// ������������ ������� �����

        // ������������ ��������� ������� �����:
        glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

        // ��������� ��������� ���� ��� ��������:
        if (finish)
        {
            glClearColor(0, 0.7, 0.7, 0);
        }
        else
        {
            glClearColor(0, 0.5, 0.5, 0);
        }

        // ������� ������:
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        // ��� ����������� ������, ����� ��������������� ������������ ��������:
        glOrtho(0, 1, 0, 1, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glColor3f(1, 1, 0); // ������ �����
        drawString(GLUT_BITMAP_TIMES_ROMAN_24, text, 0.01, 0.95);
        glPopMatrix();

        // �������� ����� ������ � �������� ��������:
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        gluPerspective(60, width / height, 1, 100);

        // �������� ����� ������ � ������� ��������:
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0, 0, distZ);	// ������ � ������� ��������� ��������� �� distZ, 

        glRotatef(angleX, 0.0f, 1.0f, 0.0f);  // ���� ���������� �� �� Oy
        glRotatef(angleY, 1.0f, 0.0f, 0.0f);  // ���� ���������� �� �� Ox
        glEnable(GL_DEPTH_TEST);	// �������� ����� ������� (��� �������� ��������� ������ ����������)

                                    // �������� ����� ��� ��������� ���������:
        glEnable(GL_LIGHTING);

        // ������ ������� ����� � 0 (�� ���� ���� �� 8), ����� ���� ������ � "����":
        glEnable(GL_LIGHT0);

        // ������� �� ������:
        for (int i = 0; i < objects; i++)
        {
            shapes[i]->draw();
        }
        for (int i = 0; i < 5; i++) {
            walls[i]->draw();
        }
        for (int i = 0; i < num + 1; i++) {
            body[i]->draw();
        }


        // �������� ���, �� ��������:
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);
        glFlush();
        // �������� ����:
        glutSwapBuffers(); // ����������� ������
    }

    // ���������� ��䳿, ���'����� � ����� ������ ���� 
    void Scene::on_size(int width, int height)
    {
        this->width = width;
        if (height == 0)
            height = 1;
        this->height = height;
    }

    // ���������� ����, ���'������ � ����������� ������ ����
    void Scene::on_mouse(int button, int state, int x, int y)
    {
        // �������� ������ ���������� ����:
        mouseX = x;
        mouseY = y;

        if ((state == GLUT_UP)) // ������ ������
        {
            this->button = -1;  // ���� ������ �� ���������
            return;
        }
        this->button = button;  // �������� ���������� ��� ������
        if (finish)
        {
            return;
        }
        
    }

    void Scene::on_motion(int x, int y)
    {
        switch (button)
        {
        case 2: // ����� ������ - ��������� �����
            angleX += x - mouseX;
            angleY += y - mouseY;
            mouseX = x;
            mouseY = y;
            break;
        }

    }
    // ���������� ����, ���'������ � ����������� �������������� ����� � ������ 
    void Scene::on_special(int key, int x, int y)
    {
        switch (key) {
        case GLUT_KEY_RIGHT:
            if (motionNum != 2)
                motionNum = 0;
            break;
        case GLUT_KEY_UP:   
            if (motionNum != 3)
                motionNum = 1;
            break;
        case GLUT_KEY_LEFT:
            if (motionNum != 0)
                motionNum = 2;
            break;
        case GLUT_KEY_DOWN: 
            if (motionNum != 1)
                motionNum = 3;
            break;
        
        case GLUT_KEY_F2:   // ���� ���
            initialize();
            break;
        }
    }

    void Scene::addBody() {
        if (num < 30) {
            num++;
            body[num] = new Body(0, 0, 0, 0.1, 0.1, 0.1, diffGray, ambiGray, specGray);
        }
    }

    void Scene::moveApple() {
        int x = rand() % 30;
        int y = rand() % 20;

        double k;
        k = x;
        k = (k - 15) / 10;
        apple->setXCenter(k);
        k = y;
        k = (k - 10) / 10;
        apple->setYCenter(k);

        for (int i = 0; i < num; i++) {
            if ((abs(body[i]->xCenter - apple->xCenter) < 0.07) && (abs(body[i]->yCenter - apple->yCenter) < 0.07)) {
                moveApple();
            }
        }
    }

    void Scene::collision() {
        for (int i = 2; i < num; i++) {
            delete shapes[i];
        }

        num = 0;
        objects = 2;
    }

    bool Scene::checkCollision(int x1, int y1, int x2, int y2) {
        if ((abs(x1 - x2) < 0.07) && (abs(y1 - y2) < 0.07))
            return true;
        else
            return false;
    }

    void Scene::motion() {

        if ((abs(body[0]->xCenter - apple->xCenter) < 0.07) && (abs(body[0]->yCenter - apple->yCenter) < 0.07)) {

            moveApple();

            addBody();
        }

        for (int i = 0; i < num; i++) {
            arr[i][0] = body[i]->xCenter;
            arr[i][1] = body[i]->yCenter;
        }
        if (!finish) {
            for (int i = 1; i <= num; i++) {
               body[i]->xCenter = arr[i - 1][0];
               body[i]->yCenter = arr[i - 1][1];
            }

            if (motionNum == 0)
                body[0]->addX(0.1);
            if (motionNum == 1)
                body[0]->addY(0.1);
            if (motionNum == 2)
                body[0]->addX(-0.1);
            if (motionNum == 3)
                body[0]->addY(-0.1);
        }

        if ((body[0]->xCenter > 1.5) || (body[0]->xCenter < -1.5))
            finish = true;
        if ((body[0]->yCenter > 1) || (body[0]->yCenter < -1.1))
            finish = true;

        for (int i = 1; i < num; i++) {
            if ((abs(body[0]->xCenter - body[i]-> xCenter) < 0.05) && (abs(body[0]->yCenter - body[i]->yCenter) < 0.05)) {
                collision();

                finish = true;
            }
        }

    }

    int tick = 0; 

    void Scene::on_timer(int value)
    {
        tick++;
        if (tick >= 40) // ���������� �������� �������
        {
            if (!finish)// ������� �����������, ���� ��� �� ��������
            {
                time++;
            }
            tick = 0;   // ������� ��������
        }
       
        on_paint();
    }

    void Scene::mainmotion(int value) {
        motion();
    }

}
