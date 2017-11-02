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
#include "SceneMgr.h"

//Renderer *g_Renderer = NULL;
SceneMgr*			g_SceneMgr = nullptr;

DWORD		g_prevTime = 0;

void Update(float fElapsedTime)
{

	g_SceneMgr->Update(fElapsedTime);
	
}
void RenderScene(void)
{
	DWORD dwStartTime = timeGetTime();
	DWORD dwElapsedTime = dwStartTime - g_prevTime;
	g_prevTime = dwStartTime;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	
	Update((float)dwElapsedTime);
	g_SceneMgr->Render();
	glutSwapBuffers();

}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//Ŭ��
		//Object* pobj = new Object;;
	//	pobj->SetInfo(OBJ_INFO(x - 250, 250 - y  , 0, 20, rand() % 10 * 0.1f, rand() % 10 * 0.1f, rand() % 10 * 0.1f, 1));
		g_SceneMgr->CreateObject(x - 250, 250 - y , 0 , OBJECT_CHARACTER);
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
	g_SceneMgr->CreateObject(0, 0, 0, OBJECT_BUILDING);

//	for ( int i = 0 ; i < MAX_OBJECTS_COUNT; ++i)
//		g_SceneMgr->CreateObject(rand() % 500 - 250, rand() % 500 - 250  , 0);
}
int main(int argc, char **argv)
{

	srand((unsigned)time(nullptr));
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
//	g_Renderer = new Renderer(500, 500);
	/*if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}*/
	g_SceneMgr = new SceneMgr;
	ObjectCreate();

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);


	g_prevTime = timeGetTime();

	glutMainLoop();

	g_SceneMgr->Clear();

    return 0;
}

