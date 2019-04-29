#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "Shader.h"
#include "Vertice.h"
#include "Modelo.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

using namespace std;

void dibujar();
void actualizar();
void inicializarTriangulo();
void inicializarCuadrado();
void teclado_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

Shader *shader;
GLuint posicionID, colorID;
GLuint modeloID, vistaID, proyeccionID;

mat4 vista, proyeccion;

Modelo *triangulo;
Modelo *cuadrado;

// Creamos una ventana
GLFWwindow *window;

int main()
{
	// Si no se puede inicializar glfw, finalizamos la ejecucion
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	// Si se pudo iniciar GLFW, entonces inicializamos la ventana
	window = glfwCreateWindow(1024, 768, "Ventana", NULL, NULL);
	
	// Si no podemos iniciar la ventana, terminamos ejecucion
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Establecemos el contexto
	glfwMakeContextCurrent(window);

	// Una vez establecido el contexto, activamos funciones modernas
	glewExperimental = true;
	GLenum errorGlew = glewInit();
	if (errorGlew != GLEW_OK) {
		cout << glewGetErrorString(errorGlew);
	}

	const GLubyte *versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL << std::endl;

	glfwSetKeyCallback(window, teclado_callback);

	inicializarTriangulo();
	inicializarCuadrado();

	const char *rutaVertex = "VertexShader.shader";
	const char *rutaFragment = "FragmentShader.shader";

	shader = new Shader(rutaVertex, rutaFragment);

	shader = new Shader(rutaVertex, rutaFragment);

	// Mapeo de atributos
	posicionID = glGetAttribLocation(shader->getID(), "posicion");
	colorID = glGetAttribLocation(shader->getID(), "color");
	transformacionesID = glGetUniformLocation(shader->getID(), "transformaciones");

	// Desenlazar el shader
	shader -> desenlazar();

	//Establecer shader al modelo
	triangulo->shader = shader;
	//Inicializar vertex array
	triangulo->inicializarVertexArray(posicionID, colorID, transformacionesID);

	cuadrado->shader = shader;
	cuadrado->inicializarVertexArray(posicionID, colorID, transformacionesID);

	// Ciclo de dibujo (Draw loop)
	while (!glfwWindowShouldClose(window)) {
		
		// Establecer region de dibujo
		glViewport(0, 0, 1024, 768);

		// Establece el color de borrado
		glClearColor(.23f, 0.3f, 0.3f, 1.0f);

		// Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Rutina de dibujo
		dibujar();
		actualizar();

		// Cambiar los buffers
		glfwSwapBuffers(window);

		// Reconocer si hay entradas
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;
}

void dibujar()
{
	triangulo->dibujar(GL_TRIANGLES);
	cuadrado->dibujar(GL_QUADS);
}

void actualizar()
{
	int estadoDerecha = glfwGetKey(window, GLFW_KEY_RIGHT);
	if (estadoDerecha == GLFW_PRESS)
	{
		triangulo->transformaciones = translate(triangulo->transformaciones, vec3(0.01f, 0.0f, 0.0f));

	}
	int estadoIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);
	if (estadoIzquierda == GLFW_PRESS)
	{
		// Nota: ten cuidado; usa floats, si no, las funciones de openglmathematics te dará, error
		triangulo->transformaciones = rotate(triangulo->transformaciones, 0.02f, vec3(0.0f, 0.0f, 1.0f));
	}
}

void teclado_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}
void inicializarTriangulo() 
{
	triangulo = new Modelo();
	Vertice v1 =
	{
		vec4(0.0f, 0.3f, 0.0f, 1.0f),
		vec4(1.0f,0.8f,0.0f,1.0f)
	};
	Vertice v2 =
	{
		vec4(-0.3f,-0.3f,0.0f, 1.0f),
		vec4(1.0f,0.8f,0.0f,1.0f)
	};
	Vertice v3 =
	{
		vec4(0.3f,-0.3f,0.0f, 1.0f),
		vec4(1.0f,0.8f,0.0f,1.0f)
	};

	triangulo->vertices.push_back(v1);
	triangulo->vertices.push_back(v2);
	triangulo->vertices.push_back(v3);
}

void inicializarCuadrado() 
{
	cuadrado = new Modelo();
	Vertice v1 = {
		vec4(-0.8f, 0.8f, 0.0f, 1.0f),
		vec4(0.4f,0.7f,0.1f,1.0f)
	};
	Vertice v2 = {
		vec4(-0.4f, 0.8f, 0.0f, 1.0f),
		vec4(0.4f,0.7f,0.1f,1.0f)
	};
	Vertice v3 = {
		vec4(-0.4f, 0.5f, 0.0f, 1.0f),
		vec4(0.4f,0.7f,0.1f,1.0f)
	};
	Vertice v4 = {
		vec4(-0.8f, 0.5f, 0.0f, 1.0f),
		vec4(0.4f,0.7f,0.1f,1.0f)
	};
	cuadrado->vertices.push_back(v1);
	cuadrado->vertices.push_back(v2);
	cuadrado->vertices.push_back(v3);
	cuadrado->vertices.push_back(v4);
}