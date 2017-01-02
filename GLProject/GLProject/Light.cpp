#include "stdafx.h"
#include "Light.h"
#include "Vector3D.h"

CSpotLight::CSpotLight()
{

}

void CSpotLight::Light(Vec3f player ,bool isOn)
{

	GLfloat AmbientLight[] = { 0, 0, 0, 1 };

		AmbientLight[0] = 0.5f;
		AmbientLight[1] = 0.5f;
		AmbientLight[2] = 0.5f;
		GLfloat AmbientLight1[] = { 0, 0, 0, 1 };
		GLfloat DiffuseLight[] = { 1.f, 1.f, 1.f, 1.0f };
		GLfloat SpecularLight[] = { 1,1,1, 1.0 };
		GLfloat	LightVertex[4];
		GLfloat spot_dir[] = { 0.0,-1.0,0.0,0.0 };
		LightVertex[0] = player.x;
		LightVertex[1] = player.y+800;
		LightVertex[2] = player.z;
		LightVertex[3] = 1;
		if (isOn) {
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			glEnable(GL_LIGHT1);
			glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
			glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
			glLightfv(GL_LIGHT0, GL_POSITION, LightVertex);

			glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight);
			glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight);
			glLightfv(GL_LIGHT1, GL_POSITION, LightVertex);

			glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30);
			glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_dir);
			glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.f);

			GLfloat gray[] = { 0.25,0.25,0.25,1.0 };
			GLfloat specref[] = { 1,1,1,1 };
			glEnable(GL_COLOR_MATERIAL);
			glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

			glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
			glMateriali(GL_FRONT, GL_SHININESS, 64);
		}
		else {
			glDisable(GL_LIGHTING);
		}
}



CSpotLight::~CSpotLight()
{
}
