#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <GL/glut.h>
#include "glm.h"
#include <iostream>
#include "Texture.h"

using namespace std;
float avanza=0,sube=0,gira=0;

class GameObject{
    public:
            GLMmodel* pModel = NULL;
            char nameTexture[100];
            Texture	loadtexture[5];
    public:
            void setTexture(char[100]);
            void setObject(char[100]);
            void positionObject(Texture loadtexture[5],GLMmodel *pModel);
};

void GameObject::setTexture(char nameTexture[100]){
      strcpy(this->nameTexture,nameTexture);
      int i;
	  if (LoadTGA(&this->loadtexture[0], this->nameTexture))
	  {
		for (i = 0; i<1; i++){
			glGenTextures(1, &this->loadtexture[i].texID);
			glBindTexture(GL_TEXTURE_2D, this->loadtexture[i].texID);
			glTexImage2D(GL_TEXTURE_2D, 0, this->loadtexture[i].bpp / 8, this->loadtexture[i].width, this->loadtexture[i].height, 0, this->loadtexture[i].type, GL_UNSIGNED_BYTE, this->loadtexture[i].imageData);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glEnable(GL_TEXTURE_2D);
			if (this->loadtexture[i].imageData)
			{
				free(this->loadtexture[i].imageData);
			}
		}
	  }

}

void GameObject::setObject(char nameObject[100]){
	this->pModel = glmReadOBJ(nameObject);

}

void GameObject::positionObject(Texture loadtexture[5],GLMmodel *pModel){

	glBindTexture(GL_TEXTURE_2D, loadtexture->texID);
	glmDraw(pModel, GLM_SMOOTH | GLM_TEXTURE);

}

GameObject nave;
GameObject tierra;
GameObject marte;
GameObject ovni;
GameObject satelite;
void init(void)
{
	glClearColor(0, 0, 0,0);
    nave.setTexture("data/Nave/textura_nave.tga");
    tierra.setTexture("data/Planeta/tierra.tga");
    marte.setTexture("data/Planeta/marte.tga");
    ovni.setTexture("data/Ovni/ovni.tga");
    satelite.setTexture("data/Satelite/satelite.tga");
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
}

void graficar(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    //Nave
    glPushMatrix();
            gluLookAt(sube,7,7, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);
	        glTranslated(sube,0,0);
            glScaled(0.005,0.005,0.005);
            glRotated(45,1,0,0);
            nave.positionObject(nave.loadtexture,nave.pModel);
    glPopMatrix();

    //Tierra
    glPushMatrix();
            glTranslated(1,0,-14);
            glScaled(0.005,0.005,0.005);
            glRotated(45,1,0,0);
            glRotated(gira,0,1,0);
            tierra.positionObject(tierra.loadtexture,tierra.pModel);
    glPopMatrix();


    //marte
    glPushMatrix();
            glTranslated(-2,0,-20);
            glScaled(0.005,0.005,0.005);
            glRotated(45,1,0,0);
            glRotated(gira,0,1,0);
            marte.positionObject(marte.loadtexture,marte.pModel);
    glPopMatrix();

    //ovni
    glPushMatrix();
            glTranslated(2,0,-5);
            glScaled(0.005,0.005,0.005);
            glRotated(15,1,0,0);
            glRotated(gira,0,1,0);
            ovni.positionObject(ovni.loadtexture,ovni.pModel);
    glPopMatrix();

    //satelite
    glPushMatrix();
            glTranslated(2,0,-12);
            glScaled(0.05,0.05,0.05);
            glRotated(15,1,0,0);
            glRotated(gira,0,1,0);
            satelite.positionObject(satelite.loadtexture,satelite.pModel);
    glPopMatrix();

	glutSwapBuffers();
}


void Special( int key, int x, int y )
{
	switch( key )
	{
		case GLUT_KEY_LEFT:
			sube -= 0.4;
			break;

		case GLUT_KEY_RIGHT:
			sube += 0.4;
			break;

		case GLUT_KEY_UP:
			gira += 0.7;
			break;

		case GLUT_KEY_DOWN:
			sube -= 0.01;
			break;
	}
}
void redimensionar(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 500.0);
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(900, 900);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("FRAPORITMOS");
	init();
	nave.setObject("data/Nave/nave.obj");
	tierra.setObject("data/Planeta/mundo.obj");
	marte.setObject("data/Planeta/mundo.obj");
    ovni.setObject("data/Ovni/ovni.obj");
    satelite.setObject("data/Satelite/satelite.obj");
	glutReshapeFunc(redimensionar);
	glutSpecialFunc( Special );
    glutDisplayFunc(graficar);
	glutIdleFunc(graficar);


    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glutMainLoop();
	return 0;
}
