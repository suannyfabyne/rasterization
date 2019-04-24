#include "main.h"

//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
	Pixel Vertice_1(128, 406, 255, 0, 0, 255);
	Pixel Vertice_2(256, 106, 0, 255, 0, 255);
	Pixel Vertice_3(384, 406, 0, 0, 255, 255);
	DrawTriangle(Vertice_1, Vertice_2, Vertice_3);

	int j = 0;

	for (int i = 128; i < 385; ++i)
	{
		Pixel Vertice_1(i, 406, 255-j, 0, 0+j, 255);
	 	Pixel Vertice_2(256, 106, 0, 255, 0, 255);
	 	j++;
		DrawLine(Vertice_1, Vertice_2);
	}

} 
//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;	

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}

