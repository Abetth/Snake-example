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
		// Видаляємо всі фігури:
		for (int i = 0; i < objects; i++)
		{
			delete shapes[i];
		}
	}
	// Ініціалізація даних:
	void Scene::initialize()
	{
		distZ = -2;
		angleX = 0;
		angleY = 0;
		time = 0;
		finish = false;
	}

	// Оброблювач події, пов'язаної з перемалюванням вікна
	void Scene::on_paint()
	{
		char text[128]; // Масив символів, 
						// Заповнення масиву символів відповідно до стану гри:
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

		// Встановлюємо область перегляду таку, щоб вона вміщувала все вікно:
		glViewport(0, 0, width, height);

		// Ініціалізуємо параметри матеріалів і джерела світла:
		float lightAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // колір фонового освітлення 
		float lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // колір дифузного освітлення 
		float lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };// колір дзеркального відображення
		float lightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f };// розташування джерела світла

		// Встановлюємо параметри джерела світла:
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

		// Визначаємо блакитний колір для очищення:
		if (finish)
		{
			glClearColor(0, 0.7, 0.7, 0);
		}
		else
		{
			glClearColor(0, 0.5, 0.5, 0);
		}

		// Очищуємо буфери:
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Для відображення тексту, краще використовувати ортографічну проекцію:
		glOrtho(0, 1, 0, 1, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glColor3f(1, 1, 0); // жовтий текст
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, text, 0.01, 0.95);
		glPopMatrix();

		// Включаємо режим роботи з матрицею проекцій:
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluPerspective(60, width / height, 1, 100);

		// Включаємо режим роботи з видовою матрицею:
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0, 0, distZ);	// камера з початку координат зсувається на distZ, 

		glRotatef(angleX, 0.0f, 1.0f, 0.0f);  // потім обертається по осі Oy
		glRotatef(angleY, 1.0f, 0.0f, 0.0f);  // потім обертається по осі Ox
		glEnable(GL_DEPTH_TEST);	// включаємо буфер глибини (для відсікання невидимих частин зображення)

									// Включаємо режим для установки освітлення:
		glEnable(GL_LIGHTING);

		// Додаємо джерело світла № 0 (їх може бути до 8), зараз воно світить з "очей":
		glEnable(GL_LIGHT0);

		// Малюємо усі фігури:
		for (int i = 0; i < objects; i++)
		{
			shapes[i]->draw();
		}

		// Вимикаємо все, що включили:
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		glFlush();
		// показуємо вікно:
		glutSwapBuffers(); // перемикання буферів

	}

	// Оброблювач події, пов'язаної зі зміною розмірів вікна 
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


	// Оброблювач подій, пов'язаних з натисканням кнопки миші
	void Scene::on_mouse(int button, int state, int x, int y)
	{
		// Зберігаємо поточні координати миші:
		switch (button)
		{
		case 2: // права кнопка - обертання сцени
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
	// Оброблювач подій, пов'язаних з натисненням функціональних клавіш і стрілок
	Scene *scene;
	void Scene::on_special(unsigned char key, int x, int y)
	{
		switch (key) {

		case GLUT_KEY_PAGE_UP:   // наближення
			if (distZ > -1.7)
			{
				break;
			}
			distZ += 0.1;
			break;
		case GLUT_KEY_PAGE_DOWN: // віддалення
			distZ -= 0.1;
			break;
		case GLUT_KEY_F2:// нова гра
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


		on_paint();     // здійснюємо перемалювання вікна

	}

	int tick = 0; // лічильник, значення якого змінюється кожні 25 мс

				  // Оброблювач події від таймера
	void Scene::on_timer(int value)
	{
		tick++;
		if (tick >= 40) // нарахували наступну секунду
		{
			if (!finish)// секунди нарощуються, якщо гру не закінчено
			{
				time++;
			}
			tick = 0;   // скинули лічильник
		}

	}

	void Scene::mainmotion(int value) {
		motion();
	}

}
