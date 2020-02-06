// PlantillaGraficos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

using namespace std;

//declarar una ventana
GLFWwindow* window;

float posXTriangulo = 0.0f, posYTriangulo = 0.0f;

double tiempoActual, tiempoAnterior;
double velocidadTriangulo = 1.0;
double rotacionTriangulo = 0.0;
double velRotaTriangulo = 200.0;
float anguloTraslacionX = cos(rotacionTriangulo);
float anguloTraslacionY = sin(rotacionTriangulo);
/*double movTrianguloX = posXTriangulo * anguloTraslacionX;
double movTrianguloY = posYTriangulo * anguloTraslacionY;*/

/*void teclado_callback(GLFWwindow* window, int key, int sacncode, int action, int mods) {
    if ((action == GLFW_PRESS || action == GLFW_REPEAT) && key == GLFW_KEY_RIGHT) {
        rotacionTriangulo += 5.0;
    }
    if ((action == GLFW_PRESS || action == GLFW_REPEAT) && key == GLFW_KEY_LEFT) {
        posXTriangulo += -0.01;
    }
    if ((action == GLFW_PRESS || action == GLFW_REPEAT) && key == GLFW_KEY_UP) {
        posYTriangulo += 0.01;
    }
    if ((action == GLFW_PRESS || action == GLFW_REPEAT) && key == GLFW_KEY_DOWN) {
        posYTriangulo += -0.01;
    }
}*/

void actualizar() {
    tiempoActual = glfwGetTime();
    double tiempoDiferencial = tiempoActual - tiempoAnterior;

    int estadoRight = glfwGetKey(window, GLFW_KEY_RIGHT);
    if (estadoRight == GLFW_PRESS) {
        rotacionTriangulo -= velRotaTriangulo * tiempoDiferencial;
    }
    int estadoUp = glfwGetKey(window, GLFW_KEY_UP);
    if (estadoUp == GLFW_PRESS) {
        posXTriangulo += (velocidadTriangulo * tiempoDiferencial) * cos((rotacionTriangulo + 90.0f) * 3.141592 / 180.0);
        posYTriangulo += (velocidadTriangulo * tiempoDiferencial) * sin((rotacionTriangulo + 90.0f) * 3.141592 / 180.0);
    }
    int estadoLeft = glfwGetKey(window, GLFW_KEY_LEFT);
    if (estadoLeft == GLFW_PRESS) {
        rotacionTriangulo += velRotaTriangulo * tiempoDiferencial;
    }
    int estadoDown = glfwGetKey(window, GLFW_KEY_DOWN);
    if (estadoDown == GLFW_PRESS) {
        posYTriangulo += -velocidadTriangulo * tiempoDiferencial;
    }

    tiempoAnterior = tiempoActual;
}

void dibujar() {
    glPushMatrix();

    glTranslatef(posXTriangulo, posYTriangulo, 0.0f);
    glRotatef(rotacionTriangulo, 0.0f, 0.0f, 1.0f);
    glScalef(0.4f, 0.7f, 0.0f);

    glBegin(GL_TRIANGLES);

    glColor3f(0.6, 0.1, 0.2);

    glVertex3f(0.0f, 0.15f, 0.0f);
    glVertex3f(-0.15f, -0.15f, 0.0f);
    glVertex3f(0.15f, -0.15f, 0.0f);

    glEnd();

    glPopMatrix();
}

int main()
{
   

    //si no se pudo iniciar GLFW terminamos ejecucion
    if (!glfwInit()){
        exit(EXIT_FAILURE);
    }
    //si se pudo iniciar GLFW iniciamos la ventana
    window = glfwCreateWindow(600, 600, "Ventana", NULL, NULL);

    //si no se pudo crear la ventana, terminamos la ejecucion
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    //establecemos la ventana como contexto
    glfwMakeContextCurrent(window);

    //una vez establecido el contexto se activan las funciiones moderna (gpu)
    glewExperimental = true;

    GLenum errores = glewInit();
    if (errores != GLEW_OK) {
        glewGetErrorString(errores);
    }

    const GLubyte* versionGL = glGetString(GL_VERSION);
    cout << "Version OpenGL: " << versionGL;

    //establecemos que con cada evento del teclado se llama a la funcion teclado_callback
    //glfwSetKeyCallback(window, teclado_callback);

    tiempoActual = glfwGetTime();
    tiempoAnterior = tiempoActual;

    //ciclo de dibujo (Draw Loop)
    while (!glfwWindowShouldClose(window)) {
        //establecer region de dibujo
        glViewport(0, 0, 600, 600);
        //establecemos el color de borrado
        //valores RGBA
        glClearColor(1, 0.8, 0, 1);
        //borrar!
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //actualizar valores y dibujar
        actualizar();
        dibujar();

        glfwPollEvents();

        glfwSwapBuffers(window);
    }
    //despues del ciclo de dibujo eliminemos la venta y procesos de glfw
    glfwDestroyWindow(window);
    glfwTerminate();
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
