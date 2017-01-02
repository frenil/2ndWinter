#include "stdafx.h"
#include "GLFramework.h"
#include "TitleScene.h"
#include "MainGameScene.h"
#include "LogoScene.h"


CGLFramework::~CGLFramework()
{
	for (auto p : m_arrScene) if (p) delete p;
}

GLvoid CGLFramework::Initialize(GLvoid)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(m_ptWindowPos.x, m_ptWindowPos.y);
	glutInitWindowSize(m_ptWindowSize.x, m_ptWindowSize.y);
	glutCreateWindow(m_szTile);
	glEnable(GL_DEPTH_TEST);
}

GLvoid CGLFramework::Reshape(int w, int h)
{
	m_ptWindowSize = Point2i { w,h };

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, h, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
}

GLvoid CGLFramework::drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	m_pCurrentScene->Render();

	glutSwapBuffers();
}

GLvoid CGLFramework::Timer(int val)
{
	m_pCurrentScene->Update();

	glutPostRedisplay();
	glutTimerFunc(m_iFPS, m_pfTimer, val);
}

GLvoid CGLFramework::SpecialKeyUp(int key, int x, int y)
{
	m_pCurrentScene->SpecialKeyUp(key, x, y);
}

GLvoid CGLFramework::SpecialKeyboard(int key, int x, int y)
{
	m_pCurrentScene->SpecialKeyboard(key, x, y);

}

GLvoid CGLFramework::Keyboard(unsigned char key, int x, int y)
{
	m_pCurrentScene->Keyboard(key, x, y);
}

GLvoid CGLFramework::Mouse(int button, int state, int x, int y)
{
	m_pCurrentScene->Mouse(button, state, x, y);
}

GLvoid CGLFramework::Run()
{
	assert((m_pfDrawScene && m_pfReshape && m_pfTimer && m_pfMouse)
		&& "No callback function has been set!");
	glClearColor(0.5, 0.5, 0.8, 1);
	
	glutSpecialUpFunc(m_pfSpecialKeyUp);
	glutSpecialFunc(m_pfSpecialKeyboard);
	glutKeyboardFunc(m_pfKeyboard);
	glutMouseFunc(m_pfMouse);
	glutDisplayFunc(m_pfDrawScene);
	glutReshapeFunc(m_pfReshape);
	glutTimerFunc(m_iFPS, m_pfTimer, 1);

	BuildScene<CTitleScene>();

	glutMainLoop();
}
