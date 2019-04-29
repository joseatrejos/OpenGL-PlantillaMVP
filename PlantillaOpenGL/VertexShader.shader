// La primera l�nea debe ser la versi�n
#version 330 core

// Atributos de entrada (vienen desde c++)
in vec4 posicion;
in vec4 color;

// Uniforms
uniform mat4 modelo;
uniform mat4 vista;
uniform mat4 proyeccion;

// Atributos de salida (van hacia el fragment shader)
out vec4 fragmentColor;

// Funcion main
void main()
{
	//Crear la matriz MVP
	mat4 MVP = proyeccion * vista * modelo;

	// Es la posici�n de salida del v�rtice
	// Es del tipo vec4 (necesita posicion en 'x', 'y', 'z' y 'w')
	gl_Position = MVP * posicion;

	// Establecer valores de atributos de salida
	fragmentColor = color;
}