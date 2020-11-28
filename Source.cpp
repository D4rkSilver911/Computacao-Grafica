#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "RgbImage.h"
#include "Materiais.h"

#define GL_SILENCE_DEPRECATION
#include <GL/freeglut.h>


//--------------------------------- Definir cores
#define BLUE     0.0, 0.0, 1.0, 1.0
#define RED		 1.0, 0.0, 0.0, 1.0
#define YELLOW	 1.0, 1.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define PI		 3.14159


//================================================================================
//===========================================================Variaveis e constantes

GLfloat tam = 1.0;
GLuint texture[10]; //3 texturas (Céu, Chão e Mesa)
RgbImage imag;

GLint malha = 0; 
GLfloat		xC = 20.0, yC = 20.0, zC = 20.0;		//.. Mundo  (unidades mundo)

static GLfloat vertices[] = {

	//……………………………………………………………………………………………………… Parte de Cima - 1 (0,1,0)
			0,  tam, 0,	// 0
			0,  tam, tam * 4,	// 1
		 tam * 2,  tam, 0,	// 2
		 tam * 2,  tam,  tam * 4,	// 3
	//……………………………………………………………………………………………………… Parte de Cima - 2  (0,1,0)
			0,  tam * 1.3f, 0,						// 4
			0,  tam * 1.3f, tam * 4,				// 5
			tam * 2,  tam * 1.3f, 0,				// 6
			tam * 2,  tam * 1.3f,  tam * 4,	// 7
	//……………………………………………………………………………………………………… Parte de Cima de Lado (Gaveta) - 1 (-1, 0, 0)
			0,  tam * 1.3f, 0,						// 8
			0,  tam, 0,									// 9
			0,  tam * 1.3f, tam * 4,				// 10
			0,  tam,  tam * 4,						// 11
	//……………………………………………………………………………………………………… Parte de Cima de Lado (Gaveta) - 2 (0, 0, -1)
			tam * 2,  tam * 1.3f, 0,						// 12
			tam * 2,  tam, 0,									// 13
			tam * 2,  tam * 1.3f, tam,				// 14
			tam * 2,  tam,  tam,						// 15
	//……………………………………………………………………………………………………… Parte de Cima de Lado (Gaveta) - 3
			0,  tam * 1.3f, 0,						// 16
			0,  tam, 0,									// 17
			tam * 2,  tam * 1.3f, 0,				// 18
			tam * 2,  tam,  0,						// 19
//……………………………………………………………………………………………………… Parte de Cima de Lado (Gaveta) - 4
			0,  tam * 1.3f, tam * 4,						// 20
			0,  tam, tam * 4,									// 21
			tam * 2,  tam * 1.3f, tam * 4,				// 22
			tam * 2,  tam,  tam * 4,						// 23
//……………………………………………………………………………………………………… Perna Esquerda - 1
			tam * 0.4f,  tam, tam * 0.4f,		// 24
			tam * 0.6f,  tam, tam * 0.4f,		// 25
			tam * 0.4f,  0, tam * 0.4f,			// 26
			tam * 0.6f,  0,  tam * 0.4f,		// 27
//……………………………………………………………………………………………………… Perna Esquerda - 2
			tam * 0.4f,  tam, tam * 0.6f,		// 28
			tam * 0.6f,  tam, tam * 0.6f,		// 29
			tam * 0.4f,  0, tam * 0.6f,			// 30
			tam * 0.6f,  0,  tam * 0.6f,		// 31
	//……………………………………………………………………………………………………… Perna Esquerda - 3
			tam * 0.4f,  tam, tam * 0.4f,		// 32
			tam * 0.4f,  tam, tam * 0.6f,		// 33
			tam * 0.4f,  0, tam * 0.4f,			// 34
			tam * 0.4f,  0,  tam * 0.6f,		// 35
	//……………………………………………………………………………………………………… Perna Esquerda - 4
			tam * 0.6f,  tam, tam * 0.4f,		// 36
			tam * 0.6f,  tam, tam * 0.6f,		// 37
			tam * 0.6f,  0, tam * 0.4f,			// 38
			tam * 0.6f,  0,  tam * 0.6f,		// 39
	//……………………………………………………………………………………………………… Perna Direita - 1
			tam * 1.4f,  tam, tam * 0.4f,		// 40
			tam * 1.6f,  tam, tam * 0.4f,		// 41
			tam * 1.4f,  0, tam * 0.4f,			// 42
			tam * 1.6f,  0,  tam * 0.4f,		// 43
	//……………………………………………………………………………………………………… Perna Direita - 2
			tam * 1.4f,  tam, tam * 0.6f,		// 44
			tam * 1.6f,  tam, tam * 0.6f,		// 45
			tam * 1.4f,  0, tam * 0.6f,			// 46
			tam * 1.6f,  0,  tam * 0.6f,		// 47
	//……………………………………………………………………………………………………… Perna Direita - 3
			tam * 1.4f,  tam, tam * 0.4f,		// 48
			tam * 1.4f,  tam, tam * 0.6f,		// 49
			tam * 1.4f,  0, tam * 0.4f,			// 50
			tam * 1.4f,  0,  tam * 0.6f,		// 51
	//……………………………………………………………………………………………………… Perna Direita - 4
			tam * 1.6f,  tam, tam * 0.4f,		// 52
			tam * 1.6f,  tam, tam * 0.6f,		// 53
			tam * 1.6f,  0, tam * 0.4f,			// 54
			tam * 1.6f,  0,  tam * 0.6f,		// 55
	//……………………………………………………………………………………………………… Perna Esquerda 2 - 1
			tam * 0.4f,  tam, tam * 3.4f,		// 56
			tam * 0.6f,  tam, tam * 3.4f,		// 57
			tam * 0.4f,  0, tam * 3.4f,			// 58
		  tam * 0.6f,  0,  tam * 3.4f,		// 59
	//……………………………………………………………………………………………………… Perna Esquerda 2 - 2
			tam * 0.4f,  tam, tam * 3.6f,		// 60
			tam * 0.6f,  tam, tam * 3.6f,		// 61
			tam * 0.4f,  0, tam * 3.6f,			// 62
			tam * 0.6f,  0,  tam * 3.6f,		// 63
	//……………………………………………………………………………………………………… Perna Esquerda 2- 3
			tam * 0.4f,  tam, tam * 3.4f,		// 64
			tam * 0.4f,  tam, tam * 3.6f,		// 65
			tam * 0.4f,  0, tam * 3.4f,			// 66
			tam * 0.4f,  0,  tam * 3.6f,		// 67
	//……………………………………………………………………………………………………… Perna Esquerda 2 - 4
			tam * 0.6f,  tam, tam * 3.4f,		// 68
			tam * 0.6f,  tam, tam * 3.6f,		// 69
			tam * 0.6f,  0, tam * 3.4f,			// 70
			tam * 0.6f,  0,  tam * 3.6f,		// 71
	//……………………………………………………………………………………………………… Perna Direita 2 - 1
			tam * 1.4f,  tam, tam * 3.4f,		// 72
			tam * 1.6f,  tam, tam * 3.4f,		// 73
			tam * 1.4f,  0, tam * 3.4f,			// 74
			tam * 1.6f,  0,  tam * 3.4f,		// 75

	//……………………………………………………………………………………………………… Perna Direita 2 - 2
			tam * 1.4f,  tam, tam * 3.6f,		// 76
			tam * 1.6f,  tam, tam * 3.6f,		// 77
			tam * 1.4f,  0, tam * 3.6f,			// 78
			tam * 1.6f,  0,  tam * 3.6f,		// 79
	//……………………………………………………………………………………………………… Perna Direita 2 - 3
			tam * 1.4f,  tam, tam * 3.4f,		// 80  
			tam * 1.4f,  tam, tam * 3.6f,		// 81
			tam * 1.4f,  0, tam * 3.4f,			// 82
			tam * 1.4f,  0,  tam * 3.6f,		// 83
	//……………………………………………………………………………………………………… Perna Direita 2 - 4
			tam * 1.6f,  tam, tam * 3.4f,		// 84
			tam * 1.6f,  tam, tam * 3.6f,		// 85
			tam * 1.6f,  0, tam * 3.4f,			// 86
			tam * 1.6f,  0,  tam * 3.6f,		// 87
	//……………………………………………………………………………………………………… Gaveta - Porta
			tam * 2,  tam * 1.3f, tam,		// 88
			tam * 2,  tam, tam,		// 89
			tam * 2,  tam * 1.3f, tam * 3,			// 90
			tam * 2,  tam,  tam * 3,		// 91
	//……………………………………………………………………………………………………… Parte de Cima de Lado (Gaveta) - 22
			tam * 2,  tam * 1.3f, tam * 3,						// 92
			tam * 2,  tam, tam * 3,									// 93
			tam * 2,  tam * 1.3f, tam * 4,				// 94
			tam * 2,  tam,  tam * 4,						// 95
	//……………………………………………………………………………………………………… Gaveta - Lado 1
			tam * 2,  tam * 1.3f, tam,		// 96
			tam * 2,  tam, tam,		// 97
			tam,  tam * 1.3f, tam,			// 98
			tam,  tam,  tam,		// 99
	//……………………………………………………………………………………………………… Gaveta - Lado 1
			tam * 2,  tam * 1.3f, tam * 3,		// 100
			tam * 2,  tam, tam * 3,		// 101
			tam,  tam * 1.3f, tam * 3,			// 102
			tam,  tam,  tam * 3,		// 103
	//……………………………………………………………………………………………………… Gaveta - Fundo
			tam * 2,  tam * 1.01f, tam,		// 104
			tam,  tam * 1.01f, tam,		// 105
			tam * 2,  tam * 1.01f, tam * 3,			// 106
			tam,  tam * 1.01f,  tam * 3,		// 107
	//……………………………………………………………………………………………………… Gaveta - Fundo
			tam,  tam * 1.3f, tam,		// 108
			tam,  tam, tam,		// 109
			tam,  tam * 1.3f, tam * 3,			// 110
			tam,  tam,  tam * 3,		// 111

			xC, 0, -xC,
			
			xC, 0, xC,
			
			-xC, 0, xC,
			
			-xC, 0, -xC,





};

static GLfloat normais[] = {

	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,


	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,


	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,

	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,

	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,

	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,

	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,

	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,

	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,

	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,

	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,

	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,

	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,

	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,

	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,

	1.0f, 0.0f, 0.0f,	
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,


		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,




	
};

//------------------------------------------------------------ Cores
static GLfloat cor[] = {
	//…………………………………………………………………………………………………… Parte de Cima 1
	0.6,  0.3, 0.0,	// 0
	0.6,  0.3, 0.0,	// 1
	0.6,  0.3, 0.0,	// 2
	0.6,  0.3, 0.0,	// 3
	//…………………………………………………………………………………………………… Parte de Cima 2
	0.6,  0.3, 0.0,	// 0
	0.6,  0.3, 0.0,	// 1
	0.6,  0.3, 0.0,	// 2
	0.6,  0.3, 0.0,	// 3
	//…………………………………………………………………………………………………… Parte de Cima de Lado - 1
	0.6,  0.3, 0.0,	// 0
	0.6,  0.3, 0.0,	// 1
	0.6,  0.3, 0.0,	// 2
	0.6,  0.3, 0.0,	// 3
	//…………………………………………………………………………………………………… Parte de Cima de Lado - 2
	0.6,  0.3, 0.0,	// 0
	0.6,  0.3, 0.0,	// 1
	0.6,  0.3, 0.0,	// 2
	0.6,  0.3, 0.0,	// 3
	//…………………………………………………………………………………………………… Parte de Cima de Lado - 3
	0.6,  0.3, 0.0,	// 0
	0.6,  0.3, 0.0,	// 1
	0.6,  0.3, 0.0,	// 2
	0.6,  0.3, 0.0,	// 3
	//…………………………………………………………………………………………………… Parte de Cima de Lado - 4
	0.6,  0.3, 0.0,	// 0
	0.6,  0.3, 0.0,	// 1
	0.6,  0.3, 0.0,	// 2
	0.6,  0.3, 0.0,	// 3
	//…………………………………………………………………………………………………… Perna Esquerda 1
	1.0,  0.55, 0.0,	// 0
	1.0,  0.55, 0.0,	// 1
	1.0,  0.55, 0.0,	// 2
	1.0,  0.55, 0.0,	// 3
	//…………………………………………………………………………………………………… Perna Esquerda 2
	1.0,  0.55, 0.0,	// 0
	1.0,  0.55, 0.0,	// 1
	1.0,  0.55, 0.0,	// 2
	1.0,  0.55, 0.0,	// 3
	//…………………………………………………………………………………………………… Perna Esquerda 3
	1.0,  0.55, 0.0,	// 0
	1.0,  0.55, 0.0,	// 1
	1.0,  0.55, 0.0,	// 2
	1.0,  0.55, 0.0,	// 3
	//…………………………………………………………………………………………………… Perna Esquerda 4
	1.0,  0.55, 0.0,	// 0
	1.0,  0.55, 0.0,	// 1
	1.0,  0.55, 0.0,	// 2
	1.0,  0.55, 0.0,	// 3
	//…………………………………………………………………………………………………… Perna Direita 1
	1.0,  0.55, 0.0,	// 0
	1.0,  0.55, 0.0,	// 1
	1.0,  0.55, 0.0,	// 2
	1.0,  0.55, 0.0,	// 3
	//…………………………………………………………………………………………………… Perna Direita 2
	1.0,  0.55, 0.0,	// 0
	1.0,  0.55, 0.0,	// 1
	1.0,  0.55, 0.0,	// 2
	1.0,  0.55, 0.0,	// 3
	//…………………………………………………………………………………………………… Perna Direita 3
	1.0,  0.55, 0.0,	// 0
	1.0,  0.55, 0.0,	// 1
	1.0,  0.55, 0.0,	// 2
	1.0,  0.55, 0.0,	// 3
	//…………………………………………………………………………………………………… Perna Direita 4
	1.0,  0.55, 0.0,	// 0
	1.0,  0.55, 0.0,	// 1
	1.0,  0.55, 0.0,	// 2
	1.0,  0.55, 0.0,	// 3
	//…………………………………………………………………………………………………… Perna Esquerda 2-1
	1.0,  0.55, 0.0,	// 0
	1.0,  0.55, 0.0,	// 1
	1.0,  0.55, 0.0,	// 2
	1.0,  0.55, 0.0,	// 3
	//…………………………………………………………………………………………………… Perna Esquerda 2-2
	1.0,  0.55, 0.0,	// 0
	1.0,  0.55, 0.0,	// 1
	1.0,  0.55, 0.0,	// 2
	1.0,  0.55, 0.0,	// 3
	//…………………………………………………………………………………………………… Perna Esquerda 2-3
	1.0,  0.55, 0.0,	// 0
	1.0,  0.55, 0.0,	// 1
	1.0,  0.55, 0.0,	// 2
	1.0,  0.55, 0.0,	// 3
	//…………………………………………………………………………………………………… Perna Esquerda 2-4
	1.0,  0.55, 0.0,	// 0
	1.0,  0.55, 0.0,	// 1
	1.0,  0.55, 0.0,	// 2
	1.0,  0.55, 0.0,	// 3
	//…………………………………………………………………………………………………… Perna Direita 2-1
	1.0,  0.55, 0.0,	// 0
	1.0,  0.55, 0.0,	// 1
	1.0,  0.55, 0.0,	// 2
	1.0,  0.55, 0.0,	// 3
	//…………………………………………………………………………………………………… Perna Direita 2-2
	1.0,  0.55, 0.0,	// 0
	1.0,  0.55, 0.0,	// 1
	1.0,  0.55, 0.0,	// 2
	1.0,  0.55, 0.0,	// 3
	//…………………………………………………………………………………………………… Perna Direita 2-3
	1.0,  0.55, 0.0,	// 0
	1.0,  0.55, 0.0,	// 1
	1.0,  0.55, 0.0,	// 2
	1.0,  0.55, 0.0,	// 3
	//…………………………………………………………………………………………………… Perna Direita 2-4
	1.0,  0.55, 0.0,	// 0
	1.0,  0.55, 0.0,	// 1
	1.0,  0.55, 0.0,	// 2
	1.0,  0.55, 0.0,	// 3
	//…………………………………………………………………………………………………… Gaveta
	0.4,  0.22, 0.13,	// 0
		0.4, 0.22, 0.13,	// 0
		0.4, 0.22, 0.13,	// 0
		0.4, 0.22, 0.13,	// 0
	//…………………………………………………………………………………………………… Parte de Cima de Lado - 22
	0.6,  0.3, 0.0,	// 0
	0.6,  0.3, 0.0,	// 1
	0.6,  0.3, 0.0,	// 2
	0.6,  0.3, 0.0,	// 3
	//…………………………………………………………………………………………………… Gaveta - Lado 1
		0.4, 0.22, 0.13,	// 0
		0.4, 0.22, 0.13,	// 0
		0.4, 0.22, 0.13,	// 0
		0.4, 0.22, 0.13,	// 0
	//…………………………………………………………………………………………………… Gaveta - Lado 2
		0.4, 0.22, 0.13,	// 0
		0.4, 0.22, 0.13,	// 0
		0.4, 0.22, 0.13,	// 0
		0.4, 0.22, 0.13,	// 0
	//…………………………………………………………………………………………………… Gaveta - Fundo
		0.2, 0.11, 0.07,	// 0
		0.2, 0.11, 0.07,	// 0
		0.2, 0.11, 0.07,	// 0
		0.2, 0.11, 0.07,	// 0
	//…………………………………………………………………………………………………… Gaveta - Lado 3
		0.2, 0.11, 0.07,	// 0
		0.2, 0.11, 0.07,	// 0
		0.2, 0.11, 0.07,	// 0
		0.2, 0.11, 0.07,	// 0
	//…………………………………………………………………………………………………… Gaveta - Lado 3
		0.2, 0.11, 0.07,	// 0
		0.2, 0.11, 0.07,	// 0
		0.2, 0.11, 0.07,	// 0
		0.2, 0.11, 0.07,	// 0

};

static GLfloat arrayTexture[] = {

1,0, 1,1, 0,1, 0,0,  // Face de cima
	1,0, 1,1, 0,1, 0,0,  // Face de baixo
	1,0, 1,1, 0,1, 0,0,  // Face de cima
	1,0, 1,1, 0,1, 0,0,  // Face de baixo
	1,0, 1,1, 0,1, 0,0,  // Face de cima
	1,0, 1,1, 0,1, 0,0,  // Face de baixo
	1,0, 1,1, 0,1, 0,0,  // Face de cima
	1,0, 1,1, 0,1, 0,0,  // Face de baixo
	1,0, 1,1, 0,1, 0,0,  // Face de cima
	1,0, 1,1, 0,1, 0,0,  // Face de baixo
	1,0, 1,1, 0,1, 0,0,  // Face de cima
	1,0, 1,1, 0,1, 0,0,  // Face de baixo
	1,0, 1,1, 0,1, 0,0,  // Face de cima
	1,0, 1,1, 0,1, 0,0,  // Face de baixo
	1,0, 1,1, 0,1, 0,0,  // Face de cima
	1,0, 1,1, 0,1, 0,0,  // Face de baixo
	1,0, 1,1, 0,1, 0,0,  // Face de cima
	1,0, 1,1, 0,1, 0,0,  // Face de baixo
	1,0, 1,1, 0,1, 0,0,  // Face de cima
	1,0, 1,1, 0,1, 0,0,  // Face de baixo
	1,0, 1,1, 0,1, 0,0,  // Face de cima
	1,0, 1,1, 0,1, 0,0,  // Face de baixo
	1,0, 1,1, 0,1, 0,0,  // Face de cima
	1,0, 1,1, 0,1, 0,0,  // Face de baixo
	1,0, 1,1, 0,1, 0,0,  // Face de cima
	1,0, 1,1, 0,1, 0,0,  // Face de baixo
	1,0, 1,1, 0,1, 0,0,  // Face de cima
	1,0, 1,1, 0,1, 0,0,  // Face de baixo
	1,0, 1,1, 0,1, 0,0,  // Face de baixo

};

//=========================================================== FACES DA MESA
GLint   					frenteVisivel = 0;
static GLuint		cima[] = { 2,3, 1,  0 };       // regra da mao direita
static GLuint		cima2[] = { 6, 7, 5, 4 };
static GLuint 		cima_lado_1[] = { 11, 10, 8, 9 }; //Parte de cima lado 1
static GLuint 		cima_lado_2[] = { 15, 14, 12, 13 }; //Parte de cima lado 2
static GLuint 		cima_lado_3[] = { 19, 18, 16, 17 }; //Parte de cima lado 3
static GLuint 		cima_lado_4[] = { 23, 22, 20, 21 }; //Parte de cima lado 4

static GLuint 		esquerda11[] = { 26, 27, 25, 24 }; //Perna Esquerda 1
static GLuint 		esquerda12[] = { 30, 31, 29, 28 }; //Perna Esquerda 2
static GLuint 		esquerda13[] = { 34, 35, 33, 32 }; //Perna Esquerda 3
static GLuint 		esquerda14[] = { 38, 39, 37, 36 }; //Perna Esquerda 4

static GLuint 		direita11[] = { 42, 43, 41, 40 }; //Perna Direita 1
static GLuint 		direita12[] = { 46, 47, 45, 44 }; //Perna Direita 2
static GLuint 		direita13[] = { 50, 51, 49, 48 }; //Perna Direita 3
static GLuint 		direita14[] = { 54, 55, 53, 52 }; //Perna Direita 4

static GLuint 		esquerda21[] = { 58, 59, 57, 56 }; //Perna Esquerda 2 1
static GLuint 		esquerda22[] = { 62, 63, 61, 60 }; //Perna Esquerda 2 2
static GLuint 		esquerda23[] = { 66, 67, 65, 64 }; //Perna Esquerda 2 3
static GLuint 		esquerda24[] = { 70, 71, 69, 68 }; //Perna Esquerda 2 4

static GLuint 		direita21[] = { 74, 75, 73, 72 }; //Perna Direita 1
static GLuint 		direita22[] = { 78, 79, 77, 76 }; //Perna Direita 2
static GLuint 		direita23[] = { 82, 83, 81, 80 }; //Perna Direita 3
static GLuint 		direita24[] = { 86, 87, 85, 84 }; //Perna Direita 4

static GLuint 		gaveta1[] = { 90, 91, 89, 88 }; //Gaveta
static GLuint 		cima_lado_22[] = { 94, 95, 93, 92 }; //Gaveta

static GLuint 		gavetalado1[] = { 98, 99, 97, 96 }; //Gaveta
static GLuint 		gavetalado2[] = { 102, 103, 101, 100 }; //Gaveta
static GLuint 		gavetafundo[] = { 106, 107, 105, 104 }; //Gaveta
static GLuint 		gavetalado3[] = { 110, 111, 109, 108 }; //Gaveta

static GLuint		chao[] = { 115, 114, 113, 112 }; //Fundo



// Objectos (sistema coordenadas)
GLint		wScreen = 800, hScreen = 600;			//.. janela (pixeis)

char     texto[30];
GLint mat = 0;
//------------------------------------------------------------ Visualizacao/Observador
GLfloat  rVisao = 10, aVisao = 0.5 * PI, incVisao = 0.2;
GLfloat  obsPinicial[] = { 1, 3, 1};
GLfloat  obsPfinal[] = {obsPinicial[0] - rVisao * cos(aVisao),
obsPinicial[1], obsPinicial[2] - rVisao * sin(aVisao) };
GLfloat  angZoom = 90;
GLfloat  incZoom = 3;

//------------------------------------------------

GLfloat xPosition = 0, yPosition = 0, zPosition = 0, angle = 0;
GLfloat xGaveta = 0, yGaveta = 0, zGaveta = 0;
GLint subir = 1, abrir = 1, obsX = 1, obsY = 1, luz = 1;


GLint materialEsp = 0;

//-------------------SKYBOX
GLUquadricObj* skyBox = gluNewQuadric();
GLfloat skySize = 30;

//-------Luzes----------------
//Ambiental
GLint dia = 1;
GLfloat intensidadeDia = 5.0f;
GLfloat luzGlobalCorAmb[] = { intensidadeDia ,intensidadeDia ,intensidadeDia , 1.0f };


GLint lampada = 1;//Lampada.
GLint int_lampada = 0;
GLfloat localizacao[] = { 1,3,2, 1 };
GLfloat lampadaDir[] = { 1.0,1.0,2.0, 1.0 };
GLfloat corAmbiente[] = { 2.0,2.0,2.0,1.0 };
GLfloat corDifusa[] = {3.0, 3.0, 3.0, 1.0};
GLfloat atConst = 2.0;

//---FOCO----
GLint luz_foco = 0;
GLint foco = 1; //Foco. 
GLfloat rFoco = 5.1, aFoco = aVisao;
GLfloat incH = 0.0, incV = 0.0;
GLfloat incMaxH = 0.5, incMaxV = yC;
GLfloat focoPini[] = { obsPinicial[0], obsPinicial[1], obsPinicial[2], 1.0 };
GLfloat focoPfin[] = { obsPinicial[0] - rFoco * cos(aFoco), obsPinicial[1], obsPinicial[2] - rFoco * sin(aFoco), 1.0 };
GLfloat focoDir[] = { focoPfin[0] - focoPini[0], 0, focoPfin[2] - focoPini[2] };
GLfloat focoExp = 10.0;
GLfloat focoCut = 60.0;

GLfloat focoCorDif[4] = { 5.0, 5.0, 5.0, 1.0 };
GLfloat focoCorEsp[4] = { 1.0, 1.0, 1.0, 1.0 };


GLfloat cSpec2[4] = { 0.8, 0.8, 0.8 };
GLfloat normal[] = { 0.0f, 1.0f, 0.0f };

GLint parede = 0;
GLint transp = 0;
GLint rubix_dif[4] = {1.0f, 1.0f, 1.0f, 0.0f};
//……………………………………………………………………………………………………………………………………



//Inicializar texturas
void init_texturas() {
	
	//-------------------------------------------------Mesa
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	imag.LoadBmpFile("madeira2.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	//-------------------------------------------------Mesa/Escura
	glGenTextures(1, &texture[3]);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	imag.LoadBmpFile("madeira_escura.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
	//-------------------------------------------------Mesa/Escura2
	glGenTextures(1, &texture[4]);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	imag.LoadBmpFile("madeira_escura_2.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	
	//---------------------------------------------------Chão
	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	imag.LoadBmpFile("chao.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	//---------------------------------------------------Céu
	glGenTextures(1, &texture[2]);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	imag.LoadBmpFile("cimento.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());


	glGenTextures(1, &texture[5]);
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	imag.LoadBmpFile("rubix.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
	
}

//Inicializar Luzes
void initLights(void) {
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);

	
		glLightfv(GL_LIGHT1, GL_POSITION, focoPini);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, focoDir);
		glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, focoExp);
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, focoCut);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, focoCorDif);
		glLightfv(GL_LIGHT1, GL_SPECULAR, focoCorEsp);
	
	
	

	glLightfv(GL_LIGHT0, GL_POSITION, localizacao);
	glLightfv(GL_LIGHT0, GL_AMBIENT, corAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, corDifusa);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, atConst);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.1);

	

	



}

//Inicializar materiais
void initMaterials(int material) {

	switch (material) {
	case 0: //……………………………………………………………………………………………esmerald
		glMaterialfv(GL_FRONT, GL_AMBIENT, esmeraldAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, esmeraldDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, esmeraldSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, esmeraldCoef);
		break;
	case 1: //……………………………………………………………………………………………jade
		glMaterialfv(GL_FRONT, GL_AMBIENT, jadeAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, jadeDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, jadeSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, jadeCoef);
		break;
	case 2: //……………………………………………………………………………………………obsidian
		glMaterialfv(GL_FRONT, GL_AMBIENT, obsidianAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, obsidianDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, obsidianSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, obsidianCoef);
		break;
	case 3: //……………………………………………………………………………………………pearl
		glMaterialfv(GL_FRONT, GL_AMBIENT, pearlAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, pearlDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, pearlSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, pearlCoef);
		break;
	case 4: //……………………………………………………………………………………………ruby
		glMaterialfv(GL_FRONT, GL_AMBIENT, rubyAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, rubyDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, rubySpec);
		glMaterialf(GL_FRONT, GL_SHININESS, rubyCoef);
		break;
	case 5: //……………………………………………………………………………………………turquoise
		glMaterialfv(GL_FRONT, GL_AMBIENT, turquoiseAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, turquoiseDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, turquoiseSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, turquoiseCoef);
		break;
	case 6: //……………………………………………………………………………………………brass
		glMaterialfv(GL_FRONT, GL_AMBIENT, brassAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, brassDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, brassSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, brassCoef);
		break;
	case 7: //……………………………………………………………………………………………bronze
		glMaterialfv(GL_FRONT, GL_AMBIENT, bronzeAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, bronzeDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, bronzeSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, bronzeCoef);
		break;
	case 8: //……………………………………………………………………………………………chrome
		glMaterialfv(GL_FRONT, GL_AMBIENT, chromeAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, chromeDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, chromeSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, chromeCoef);
		break;
	case 9: //……………………………………………………………………………………………copper
		glMaterialfv(GL_FRONT, GL_AMBIENT, copperAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, copperDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, copperSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, copperCoef);
		break;
	case 10: //……………………………………………………………………………………………gold
		glMaterialfv(GL_FRONT, GL_AMBIENT, goldAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, goldDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, goldSpec);

		//glMaterialf(GL_FRONT, GL_SHININESS, goldSpec);
		if (materialEsp) {
			glMaterialf(GL_FRONT, GL_SHININESS, 5);
		}
		else {
			glMaterialf(GL_FRONT, GL_SHININESS, 120);
		}
			
		break;
	case 11: //……………………………………………………………………………………………silver
		glMaterialfv(GL_FRONT, GL_AMBIENT, silverAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, silverDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, silverSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, silverCoef);
		break;
	case 12: //……………………………………………………………………………………………blackPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, blackPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, blackPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, blackPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, blackPlasticCoef);
		break;
	case 13: //……………………………………………………………………………………………cyankPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, cyanPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, cyanPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, cyanPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, cyanPlasticCoef);
		break;
	case 14: //……………………………………………………………………………………………greenPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, greenPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, greenPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, greenPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, greenPlasticCoef);
		break;
	case 15: //……………………………………………………………………………………………redPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, redPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, redPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, redPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, redPlasticCoef);
		break;
	case 16: //……………………………………………………………………………………………yellowPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, whitePlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, whitePlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, whitePlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, whitePlasticCoef);
		break;
	case 17: //……………………………………………………………………………………………yellowPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, yellowPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, yellowPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, yellowPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, yellowPlasticCoef);
		break;
	case 18: //……………………………………………………………………………………………blackRubber
		glMaterialfv(GL_FRONT, GL_AMBIENT, blackRubberAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, blackRubberDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, blackRubberSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, blackRubberCoef);
		break;
	case 19: //……………………………………………………………………………………………cyanRubber
		glMaterialfv(GL_FRONT, GL_AMBIENT, cyanRubberAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, cyanRubberDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, cyanRubberSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, cyanRubberCoef);
		break;
	case 20: //……………………………………………………………………………………………greenRubber
		glMaterialfv(GL_FRONT, GL_AMBIENT, greenRubberAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, greenRubberDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, greenRubberSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, greenRubberCoef);
		break;
	case 21: //……………………………………………………………………………………………redRubber
		glMaterialfv(GL_FRONT, GL_AMBIENT, redRubberAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, redRubberDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, redRubberSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, redRubberCoef);
		break;
	case 22: //……………………………………………………………………………………………redRubber
		glMaterialfv(GL_FRONT, GL_AMBIENT, whiteRubberAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, whiteRubberDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, whiteRubberSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, whiteRubberCoef);
		break;
	case 23: //……………………………………………………………………………………………redRubber
		glMaterialfv(GL_FRONT, GL_AMBIENT, yellowRubberAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, yellowRubberDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, yellowRubberSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, yellowRubberCoef);
		break;
	}
}


void inicializa(void) 
{
	glClearColor(BLACK);	
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	init_texturas();
	initLights();
	initMaterials(1);
	



	glVertexPointer(3, GL_FLOAT, 0, vertices); //………………………………………VertexArrays: vertices + normais + cores + textura
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, cor);
	glEnableClientState(GL_COLOR_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normais);
	glEnableClientState(GL_NORMAL_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, arrayTexture);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

}

//Cubo
void draw_cubo(int size, int textura){

	static GLfloat n[6][3] = {
	  {-1.0, 0.0, 0.0},
	  {0.0, 1.0, 0.0},
	  {1.0, 0.0, 0.0},
	  {0.0, -1.0, 0.0},
	  {0.0, 0.0, 1.0},
	  {0.0, 0.0, -1.0}
	};
	static GLint faces[6][4] = {
	  {0, 1, 2, 3},
	  {3, 2, 6, 7},
	  {7, 6, 5, 4},
	  {4, 5, 1, 0},
	  {5, 6, 2, 1},
	  {7, 4, 0, 3}
	};
	GLfloat v[8][3];
	GLint i;

	
	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size/2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = size/2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size/2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = size/2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size/2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = size/2;
	
	glEnable(GL_TEXTURE_2D);

	for (i = 5; i >= 0; i--) {
		glBindTexture(GL_TEXTURE_2D, texture[textura]);
		if (transp) initMaterials(9);
		else initMaterials(16);
		glPushMatrix();
		glBegin(GL_QUADS);
		glNormal3fv(&n[i][0]);
		glTexCoord2f(0, 0);   glVertex3fv(&v[faces[i][0]][0]);
		glTexCoord2f(1, 0);   glVertex3fv(&v[faces[i][1]][0]);
		glTexCoord2f(1, 1);   glVertex3fv(&v[faces[i][2]][0]);
		glTexCoord2f(0, 1);   glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
		glPopMatrix();
	}
	glDisable(GL_TEXTURE_2D);
}

//Chão
void desenhaQuadrado()
{
	//------------------------------------ deswnhado na origem 
	if (malha) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		initMaterials(16);
		GLint tam, tam2;
		for (tam2 = -xC; tam2 < xC; tam2++) {
			for (tam = -xC; tam < xC; tam++) {
				glPushMatrix();
				glBegin(GL_QUADS);
				glNormal3fv(normal);
				glTexCoord2f(0, 0);
				glVertex3f(tam, 0, tam2 + 1);
				glNormal3fv(normal);
				glTexCoord2f(1, 0);
				glVertex3f(tam + 1, 0, tam2 + 1);
				glNormal3fv(normal);
				glTexCoord2f(0, 1);
				glVertex3f(tam + 1, 0, tam2);
				glNormal3fv(normal);
				glTexCoord2f(1, 1);
				glVertex3f(tam, 0, tam2);
				glEnd();
				glPopMatrix();

			}



		}

		glDisable(GL_TEXTURE_2D);
	}
	else {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		initMaterials(16);
	

				glPushMatrix();
				glBegin(GL_QUADS);
				glNormal3fv(normal);
				glTexCoord2f(0, 0);
				glVertex3f(-xC, 0, zC);
				glNormal3fv(normal);
				glTexCoord2f(1, 0);
				glVertex3f(xC, 0, zC);
				glNormal3fv(normal);
				glTexCoord2f(0, 1);
				glVertex3f(xC, 0, -zC);
				glNormal3fv(normal);
				glTexCoord2f(1, 1);
				glVertex3f(-xC, 0, -zC);
				glEnd();
				glPopMatrix();

			

				glDisable(GL_TEXTURE_2D);	

	}

		
	
	
}

//Paredes
void desenhaparedes(int paredes)
{
	//------------------------------------ deswnhado na origem
	GLint tam, tam2;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	if (parede) {
		initMaterials(19);
	}
	else {
		initMaterials(22);
	}
	switch (paredes) {
	case 1:
		for (tam2 = yC; tam2 > 0; tam2-=0.5) {
			for (tam = -zC; tam < zC; tam++) {
				glPushMatrix();
				glBegin(GL_QUADS);
				glNormal3fv(normal);
				glTexCoord2f(0, 0);
				glVertex3f(xC, 0, tam);
				glNormal3fv(normal);
				glTexCoord2f(1, 0);
				glVertex3f(xC, 0, tam + 1);
				glNormal3fv(normal);
				glTexCoord2f(0, 1);
				glVertex3f(xC, tam2, tam + 1);
				glNormal3fv(normal);
				glTexCoord2f(1, 1);
				glVertex3f(xC, tam2, tam);
				glEnd();
				glPopMatrix();

			}
		}
		glDisable(GL_TEXTURE_2D);

		break;


	case 2:
		for (tam2 = yC; tam2 > 0; tam2--) {
			for (tam = -zC; tam < zC; tam++) {
				glPushMatrix();
				glBegin(GL_QUADS);
				glNormal3fv(normal);
				glTexCoord2f(0, 0);
				glVertex3f(-xC, 0, tam);
				glNormal3fv(normal);
				glTexCoord2f(1, 0);
				glVertex3f(-xC, 0, tam + 1);
				glNormal3fv(normal);
				glTexCoord2f(0, 1);
				glVertex3f(-xC, tam2, tam + 1);
				glNormal3fv(normal);
				glTexCoord2f(1, 1);
				glVertex3f(-xC, tam2, tam);
				glEnd();
				glPopMatrix();

			}



		}

		glDisable(GL_TEXTURE_2D);

		break;

	case 3:
		for (tam2 = yC; tam2 > 0; tam2--) {
			for (tam = -xC; tam < xC; tam++) {
				glPushMatrix();
				glBegin(GL_QUADS);
				glNormal3fv(normal);
				glTexCoord2f(0, 0);
				glVertex3f(tam, 0, -zC);
				glNormal3fv(normal);
				glTexCoord2f(1, 0);
				glVertex3f(tam+1, 0, -zC);
				glNormal3fv(normal);
				glTexCoord2f(0, 1);
				glVertex3f(tam + 1, tam2, -zC);
				glNormal3fv(normal);
				glTexCoord2f(1, 1);
				glVertex3f(tam, tam2, -zC);
				glEnd();
				glPopMatrix();

			}



		}

		glDisable(GL_TEXTURE_2D);

		break;

	case 4:
		for (tam2 = yC; tam2 > 0; tam2--) {
			for (tam = -xC; tam < xC; tam++) {
				glPushMatrix();
				glBegin(GL_QUADS);
				glNormal3fv(normal);
				glTexCoord2f(0, 0);
				glVertex3f(tam, 0, zC);
				glNormal3fv(normal);
				glTexCoord2f(1, 0);
				glVertex3f(tam + 1, 0, zC);
				glNormal3fv(normal);
				glTexCoord2f(0, 1);
				glVertex3f(tam + 1, tam2, zC);
				glNormal3fv(normal);
				glTexCoord2f(1, 1);
				glVertex3f(tam, tam2, zC);
				glEnd();
				glPopMatrix();

			}



		}

		glDisable(GL_TEXTURE_2D);

		break;
	}


}

//Auxiliar
void desenhaTexto(char* string, GLfloat x, GLfloat y, GLfloat z)
{
	glRasterPos3f(x, y, z);
	while (*string)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *string++);
}

//Rubix Cube
void draw_rubix() {
	
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTranslatef(xPosition, yPosition, zPosition);
	glRotatef(angle, 0.0, 1.0, 0.0);
	
	glTranslatef(1, 1.5, 2);
	glScalef(0.2, 0.2, 0.2);
	draw_cubo(2, 5);
	glPopMatrix();
	glDisable(GL_BLEND);
 }

/*Desenhar todos os elementos da cena*/
void drawScene() {

	//==================================== MESA
	//
	
	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	initMaterials(10);
	glPushMatrix();

	glTranslatef(xPosition, yPosition, zPosition);
	
	glRotatef(angle, 0.0, 1.0, 0.0);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);   // desenhar uma das faces da mesa (0,1,0)
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima2);   // desenhar uma das faces da mesa (0,1,0)
	
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima_lado_1);   // desenhar uma das faces da mesa (-1,0,0)
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima_lado_2);   // desenhar uma das faces da mesa (1,0,0)
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima_lado_3);   // desenhar uma das faces da mesa (0,0,-1)
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima_lado_4);   // desenhar uma das faces da mesa (0,0,1)

	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda11);   // desenhar uma das faces da mesa (0,0,-1)
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda12);   // desenhar uma das faces da mesa (0,0,1)
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda13);   // desenhar uma das faces da mesa (-1,0,0)
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda14);   // desenhar uma das faces da mesa (1,0,0)

	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita11);   // desenhar uma das faces da mesa (0,0,-1)
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita12);   // desenhar uma das faces da mesa (0,0,1)
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita13);   // desenhar uma das faces da mesa (1,0,0)
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita14);   // desenhar uma das faces da mesa (-1,0,0)

	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda21);   // desenhar uma das faces da mesa (0,0,-1)
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda22);   // desenhar uma das faces da mesa (0,0,1)
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda23);   // desenhar uma das faces da mesa (-1,0,0)
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda24);   // desenhar uma das faces da mesa (1,0,0)

	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita21);   // desenhar uma das faces da mesa (0,0,-1)
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita22);   // desenhar uma das faces da mesa (0,0,1)
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita23);   // desenhar uma das faces da mesa (-1,0,0)
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita24);   // desenhar uma das faces da mesa (1,0,0)

	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima_lado_22);   // desenhar uma das faces da mesa (1,0,0)
	glPopMatrix();

	
	

	glDisable(GL_TEXTURE_2D);

	

	
	/*------------Gaveta------------------*/
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	initMaterials(10);
	glPushMatrix();
	glTranslatef(xPosition, yPosition, zPosition);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glTranslatef(xGaveta, yGaveta, zGaveta);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, gaveta1);   // desenhar uma das faces da mesa (1,0,0)
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, gavetalado1);   // desenhar uma das faces da mesa(0,0,-1)
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, gavetalado2);   // desenhar uma das faces da mesa (0,0,1)
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	
	/*----Fundo da Gaveta (Mais Escuro)----*/
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	initMaterials(10);
	glPushMatrix();
	glTranslatef(xPosition, yPosition, zPosition);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glTranslatef(xGaveta, yGaveta, zGaveta);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, gavetafundo);   // desenhar uma das faces da mesa (0,1,0)
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, gavetalado3);   // desenhar uma das faces da mesa (1,0,0)
	glPopMatrix();
	//glFrontFace(GL_CCW);
	glDisable(GL_TEXTURE_2D);
	
	
	//--------------Chão---------------


	desenhaQuadrado();
	
	//-------------Paredes----------------------

	
	desenhaparedes(1);
	desenhaparedes(2);
	desenhaparedes(3);
	desenhaparedes(4);
	
}

 /*Desenhar os Eixos, foi para auxiliar na meta 1 a desenhar os vertices*/
void drawEixos()
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo X
	glColor4f(RED);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(10, 0, 0);
	glEnd();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Y
	glColor4f(GREEN);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 10, 0);
	glEnd();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Z
	glColor4f(BLUE);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 0, 10);
	glEnd();

}

void display(void) {
	glClearColor(0, 0, 0, 1.0);
	//================================================================= APaga ecran e lida com profundidade (3D)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	/*---Apenas 1 viewport por agora---*/

	glEnable(GL_LIGHTING);
	glViewport(0, 0, wScreen * 2, hScreen * 2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angZoom, (float)wScreen / hScreen, 0.1, 3 * zC);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsPinicial[0], obsPinicial[1], obsPinicial[2], obsPfinal[0], obsPfinal[1], obsPfinal[2], 0, 1, 0);
	 /*
	sprintf(texto, "(%.2f, %.2f, %.2f)", focoPfin[0], focoPfin[1], focoPfin[2]);
	desenhaTexto(texto, obsPfinal[0], obsPfinal[1], obsPfinal[2]);
	*/
	initLights();

	//…………………………………………………………………………………………………………………………………………………………Objectos
	//drawEixos();
	drawScene();
	draw_rubix();
	

	//. . . . . . . . . . . . . . . . . . . . .  Actualizacao
	glutSwapBuffers();
}

void atualiza_visao() {
	obsPfinal[0] = obsPinicial[0] + rVisao * cos(aVisao);
	obsPfinal[2] = obsPinicial[2] - rVisao * sin(aVisao);

	
	focoPini[0] = obsPinicial[0];
	focoPini[2] = obsPinicial[2];
	focoPfin[0] = focoPini[0] - rFoco * cos(aFoco + incH);
	focoPfin[2] = focoPini[2] - rFoco * sin(aFoco + incH);
	focoPini[1] = obsPinicial[1];
	focoPini[2] = obsPinicial[2];
	focoDir[0] = focoPfin[0] - focoPini[0];
	focoDir[1] = incV;
	focoDir[2] = focoPfin[2] - focoPini[2];

	
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {


	switch (key) {

	case 'N':
	case 'n':
		incH = incH - 0.05;
		if (incH < -incMaxH) incH = -incMaxH;
		atualiza_visao();
		break;
	case 'M':
	case 'm':
		incH = incH + 0.05;
		if (incH > incMaxH) incH = incMaxH;
		atualiza_visao();

		break;
	case 'U':
	case 'u':
		incV = incV + 0.05;
		if (incV > incMaxV) incV = incMaxV;
		atualiza_visao();
		break;
	case 'J':
	case 'j':
		incV = incV - 0.05;
		if (incV < -incMaxV) incV = -incMaxV;
		atualiza_visao();
		break;

	case 'A':
	case 'a':
		obsPinicial[1] += 1;
		atualiza_visao();
		break;

	case 'S':
	case 's':
		if (obsPinicial[1] - 1 > 0) {
			obsPinicial[1] -= 1;
			atualiza_visao();

		}
		break;
	case 'e':
	case 'E':
		angle = angle + 5;
		glutPostRedisplay();
		break;

	case 'd':
	case 'D':
		angle = angle - 5;
		glutPostRedisplay();
		break;
	case 'p':
	case 'P':
		if (abrir) {
			xGaveta += 0.05;
			if (xGaveta > 1) {
				abrir = 0;
			}
		}
		else {
			xGaveta -= 0.05;
			if (xGaveta < 0) {
				abrir = 1;
			}
		}
		glutPostRedisplay();
		break;

	case 'l':
	case 'L':
		dia = !dia;
		
		if (dia) { luzGlobalCorAmb[0] = 5.0;   luzGlobalCorAmb[1] = 5.0;   luzGlobalCorAmb[2] = 5.0; glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		}
		else { luzGlobalCorAmb[0] = 0.2;   luzGlobalCorAmb[1] = 0.2;   luzGlobalCorAmb[2] = 0.2; }
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);
		glutPostRedisplay();
		break;
		

	case 't':
	case 'T':
		if (!dia) {
		lampada = !lampada;
		
			if (lampada)
				glEnable(GL_LIGHT0);
			else
				glDisable(GL_LIGHT0);

		}
		glutPostRedisplay();
		break;
		
	case 'f':
	case 'F':
		
		
	
		if (!dia) {
			foco = !foco;
			if (foco)
				glEnable(GL_LIGHT1);
			else
				glDisable(GL_LIGHT1);
		}
		
		glutPostRedisplay();
		break;

	case 'r':
	case 'R':
		luz_foco = !luz_foco;
		if (luz_foco) {
			focoCorDif[0] = 1.5; focoCorDif[1] = 0.0; focoCorDif[2] = 0.0;
			focoCorEsp[0] = 1.5; focoCorEsp[1] = 0.0; focoCorEsp[2] = 0.0;
		}
		else {
			focoCorDif[0] = 5.0; focoCorDif[1] = 5.0; focoCorDif[2] = 5.0;
			focoCorEsp[0] = 1.0; focoCorEsp[1] = 1.0; focoCorEsp[2] = 1.0;

		}
		if (!dia) {
			glLightfv(GL_LIGHT1, GL_DIFFUSE, focoCorDif);
			glLightfv(GL_LIGHT1, GL_SPECULAR, focoCorEsp);

		}
		
		glutPostRedisplay();
		break;

	case 'I':
	case 'i':
		int_lampada = !int_lampada;
		if (int_lampada) {
			corDifusa[0] = 10.0; corDifusa[1] = 10.0; corDifusa[2] = 10.0;
		}
		else {
			corDifusa[0] = 5.0; corDifusa[1] = 5.0; corDifusa[2] = 5.0;
		}
		


		if (!dia) {
			glLightfv(GL_LIGHT0, GL_DIFFUSE, corDifusa);
		}
		glutPostRedisplay();
		break;

	case 'Y':
	case 'y':
		parede = !parede;
	
		
		glutPostRedisplay();
		break;

	case 'Q':
	case 'q':
		transp = !transp;
		glutPostRedisplay();
		break;

	case 'Ç':
	case 'ç':
		materialEsp = !materialEsp;
		glutPostRedisplay();
		break;

	case 'Z':
	case 'z':
		malha = !malha;


		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	}

}

void teclasNotAscii(int key, int x, int y) {

	if (key == GLUT_KEY_UP) {
	
			obsPinicial[0] = (obsPinicial[0] + incVisao * cos(aVisao));

			obsPinicial[2] = (obsPinicial[2] - incVisao * sin(aVisao));
		
		

	}
	if (key == GLUT_KEY_DOWN) {
		obsPinicial[0] = (obsPinicial[0] - incVisao * cos(aVisao));
		obsPinicial[2] = (obsPinicial[2] + incVisao * sin(aVisao));
	}
	if (key == GLUT_KEY_LEFT) {
		aVisao = (aVisao + 0.1);
		aFoco = aFoco - 0.1;
	}

	if (key == GLUT_KEY_RIGHT){
		aVisao = (aVisao - 0.1);
		aFoco = aFoco + 0.1;
	
	}
	
	atualiza_visao();
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("Projeto Mesa ||Observador:'SETAS'||Inclinar-'a/s'||Abrir/Fechar Gaveta-'p'||Dia/Noite: 'L'|| Foco: 'F'||Controlar Foco:'n/m/j/u'|| Lampada: 'T'||Mudar Cor Foco: 'R'|Mudar Intensidade Lampada: 'I'| Mudar material da parede: 'Y'| Cubo transparente: 'Q'| Comp.Especular Material: 'Ç' | Usar Malha: 'Z' ");

	inicializa();

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}
