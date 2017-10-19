#include "stdafx.h"
#include "MainGame.h"

CMainGame* g_MainGame = nullptr;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
	
	g_MainGame->Render();
	//랜더
	glutSwapBuffers();
}

void Idle(void)
{
	g_MainGame->Update();
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

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);//optional
	glutInitWindowSize(WINCX, WINCY); //optional
	glutCreateWindow("JWH FRAMEWORK");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		cout << "GLEW 3.0 not supported\n ";
	}
	// 메인 게임 생성
	g_MainGame = new CMainGame();
	g_MainGame->Initialize();


	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	if (g_MainGame)
	{
		delete g_MainGame;
	}

	return 0;
}

