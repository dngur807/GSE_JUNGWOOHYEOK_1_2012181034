/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include "Renderer.h"
#include "Object.h"

Renderer *g_Renderer = NULL;
vector<Object*>		g_vecObject;

void Update()
{
	for (Object* pobj : g_vecObject)
	{
		pobj->Update();
	}
}
void RenderScene(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	for (Object* pobj : g_vecObject)
	{

		g_Renderer->DrawSolidRect(pobj->GetInfo().vPos.x, pobj->GetInfo().vPos.y, pobj->GetInfo().vPos.z
			, pobj->GetInfo().size
			, pobj->GetInfo().r, pobj->GetInfo().g, pobj->GetInfo().b, pobj->GetInfo().a);
	}

	glutSwapBuffers();
}

void Idle(void)
{
	Update();
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//Å¬¸¯
		Object* pobj = new Object;;
		pobj->SetInfo(OBJ_INFO(x - 250, 250 - y  , 0, 20, rand() % 10 * 0.1f, rand() % 10 * 0.1f, rand() % 10 * 0.1f, 1));
		g_vecObject.push_back(pobj);
	}
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}
void ObjectCreate()
{
	Object* pobj = nullptr;
	
	for (int i = 0; i < 1; ++i)
	{
		pobj = new Object;
		pobj->SetInfo(OBJ_INFO(rand() % 250 , i * 40   - 250 + 20, 0, 20, i * 0.01f, i *  0.02f, i *  0.11f, 1));
		g_vecObject.push_back(pobj);
	}
	
}
int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	ObjectCreate();

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;
	for (Object* pobj : g_vecObject)
	{
		delete pobj;
	}
	g_vecObject.clear();
    return 0;
}

