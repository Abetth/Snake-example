#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <fstream>
#include <gl/glut.h>
#include <stdio.h>
#include "Scene.h"
#include "Body.h"
#include "utils.h"
#include "Apple.h"
#include <typeinfo>




namespace SnakeGame
{
	using namespace GraphUtils;

	Scene::Scene(float xStep, float zStep)
	{
		motionNum = 0;
		apple = new Apple(1, 0, 0, 0.05, 0.05, 0.05, diffRed, ambiRed, specRed);
		shapes[objects] = apple;
		objects++;

		body[0] = new Body(0, 0, 0, 0.1, 0.1, 0.1, diffGreen, ambiGreen, specGreen);
		shapes[objects] = body[0];
		objects++;

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
	// ����������� �����:
	void Scene::initialize()
	{
		distZ = -2;
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
			sprintf(text, "Game over.Time: %d sec. Record: %d  F2 - Restart game   Esc - Exit", time, record);
			if (time > record)
			{
				std::ofstream out;
				out.open("record.txt");
				out << time << std::endl;
				out.close();
			}
		}
		else
		{
			std::ifstream in;
			in.open("record.txt");
			in >> record;
			in.close();
			sprintf(text, "F2 - Restart game   Esc - Exit      Record: %d. Time: %d sec.", record, time);

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
	void Scene::resetView()
	{
		distZ = -2;
		angleX = 0;
		angleY = 0;
	}


	// ���������� ����, ���'������ � ����������� ������ ����
	void Scene::on_mouse(int button, int state, int x, int y)
	{
		// �������� ������ ���������� ����:
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
	void Scene::deleteShapes()
	{
		shapes[objects] = body[0];
		objects--;
		for (int i = 0; i < num; i++) {
			shapes[objects] = body[num];
			objects--;
		}
		shapes[objects] = apple;
		objects--;
		for (int i = 0; i < num; i++) {
			if ((abs(body[i]->xCenter - apple->xCenter) < 0.07) && (abs(body[i]->yCenter - apple->yCenter) < 0.07)) {
				moveApple();
			}

		}
		num = 0;
		body[0] = new Body(0, 0, 0, 0.1, 0.1, 0.1, diffGreen, ambiGreen, specGreen);
		shapes[objects] = body[0];
		objects++;

		apple = new Apple(1, 0, 0, 0.05, 0.05, 0.05, diffRed, ambiRed, specRed);
		shapes[objects] = apple;
		objects++;
		for (int i = 0; i < num; i++) {
			if ((abs(body[i]->xCenter - apple->xCenter) < 0.07) && (abs(body[i]->yCenter - apple->yCenter) < 0.07)) {
				moveApple();
			}

		}
	}
	// ���������� ����, ���'������ � ����������� �������������� ����� � ������
	Scene *scene;
	void Scene::on_special(unsigned char key, int x, int y)
	{
		switch (key) {

		case GLUT_KEY_PAGE_UP:   // ����������
			if (distZ > -1.7)
			{
				break;
			}
			distZ += 0.1;
			break;
		case GLUT_KEY_PAGE_DOWN: // ���������
			distZ -= 0.1;
			break;
		case GLUT_KEY_F2:// ���� ���
			deleteShapes();
			initialize();
			break;
		case GLUT_KEY_F3:
			resetView();
			break;
		case GLUT_KEY_UP:
			if (motionNum != 3)
				motionNum = 1;
			break;
		case GLUT_KEY_DOWN:
			if (motionNum != 1)
				motionNum = 3;
			break;
		case GLUT_KEY_LEFT:
			if (motionNum != 0)
				motionNum = 2;
			break;
		case GLUT_KEY_RIGHT:
			if (motionNum != 2)
				motionNum = 0;
			break;
		}
	}

	void Scene::addBody() {
		if (num < 30) {
			num++;
			body[num] = new Body(0, 0, 0, 0.1, 0.1, 0.1, diffGray, ambiGray, specGray);
			shapes[objects] = body[num];
		}
		objects++;

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

	void Scene::motion() {

		std::cout << std::endl << "apple: " << apple->xCenter << " " << apple->yCenter;
		std::cout << "head: " << body[0]->xCenter << " " << body[0]->yCenter;
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
			body[0]->xCenter *= -1;
		if ((body[0]->yCenter > 1) || (body[0]->yCenter < -1.2))
			body[0]->yCenter = body[0]->yCenter * -1 - 0.2;


		for (int i = 1; i < num; i++) {
			if ((abs(body[0]->xCenter - body[i]->xCenter) < 0.05) && (abs(body[0]->yCenter - body[i]->yCenter) < 0.05)) {
				collision();
				finish = true;
			}
		}


		on_paint();     // ��������� ������������� ����

	}

	int tick = 0; // ��������, �������� ����� ��������� ���� 25 ��

				  // ���������� ��䳿 �� �������
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

	}

	void Scene::mainmotion(int value) {
		motion();
	}

}
