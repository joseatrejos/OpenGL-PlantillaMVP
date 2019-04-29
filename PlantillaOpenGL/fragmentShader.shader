// La primer linea debe ser la versión
#version 330 core

// Atributos de entrada (vienen desde el Vertex Shader)
in vec4 fragmentColor;

// Atributos de salida (van hacia el búfer)
out vec4 salidaColor;

// Función main
void main()
{
	salidaColor = fragmentColor;
}