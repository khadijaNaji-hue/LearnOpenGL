#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include "shader.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

int main()
{

    // glfw init
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // CREATE GLFW WINDOW
    GLFWwindow *window = glfwCreateWindow(800, 600, "SHADERS_CH", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW WINDOW" << std::endl;
        glfwTerminate();
        return 0;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGl funs pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "faild init glad" << std::endl;
        return -1;
    }

    // our shader program
    Shader ourshader("../shaders/shader.vs", "../shaders/shader.fs");
    Shader ourshader1("../shaders/shader1.vs", "../shaders/shader.fs");
    float timeValue;
    float greenValue, redValue , angle;
    unsigned int VAO_T, VBO_T , EBO_T , VAO_S , VBO_S , EBO_S;
    glGenBuffers(1, &VBO_T);
    glGenVertexArrays(1, &VAO_T);
    glGenBuffers(1, &EBO_T);

    glGenBuffers(1, &VBO_S);
    glGenVertexArrays(1, &VAO_S);
    glGenBuffers(1, &EBO_S);

    // vertec data
    int offset = 60 ;
    float Trianglevertices[] = {
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f , -0.4f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.3f, -0.4f, 0.0f, 1.0f, 0.82f, 0.86f ,0.0f ,

        0.0f , -0.4f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.3f, -0.4f, 0.0f, 1.0f, 0.82f, 0.86f ,1.0f,

        0.0f , -0.4f, 0.0f, 0.0f, 1.0f, 0.0f, 2.0f,
        0.3f, -0.4f, 0.0f, 1.0f, 0.82f, 0.86f, 2.0f,

        0.0f , -0.4f, 0.0f, 0.0f, 1.0f, 0.0f, 3.0f,
        0.3f, -0.4f, 0.0f, 1.0f, 0.82f, 0.86f ,3.0f,

        0.0f , -0.4f, 0.0f, 0.0f, 1.0f, 0.0f, 4.0f,
        0.3f, -0.4f, 0.0f, 1.0f, 0.82f, 0.86f ,4.0f,

        0.0f , -0.4f, 0.0f, 0.0f, 1.0f, 0.0f, 5.0f,
        0.3f, -0.4f, 0.0f, 1.0f, 0.82f, 0.86f ,5.0f

    };
    int indices[] = {
        0, 1, 2,
        0, 3 , 4,
        0 , 5 , 6,
        0 , 7 , 8,
        0 , 9 , 10,
        0 , 11 , 12
    };

    float Squarevertices[] = {
        -0.01f , 0.0f ,0.0f ,0.55f, 0.55f, 0.6f,
        0.01f , 0.0f ,0.0f ,0.55f, 0.55f, 0.6f,
        -0.01f , -0.95f ,0.0f ,0.9f , 0.9f , 0.92f ,
        0.01f , -0.95f ,0.0f ,0.9f , 0.9f , 0.92f
    };
    int indices_S[] = {
        0 , 1 , 2 ,
        1 , 2 , 3
    };
    glBindVertexArray(VAO_T);
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBO_T);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Trianglevertices), Trianglevertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_T);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // SET ATTRIUBUTE
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
    glBindVertexArray(0);

    glBindVertexArray(VAO_S);
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBO_S);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Squarevertices), Squarevertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_S);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_S), indices_S, GL_STATIC_DRAW);

        // SET ATTRIUBUTE
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // rendering commands here

        glClearColor(1.0f, 1.0f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ourshader1.use();
        glBindVertexArray(VAO_S);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        ourshader.use();
        glBindVertexArray(VAO_T);
        angle  = glfwGetTime() ;
        ourshader.setFloat("angle", angle);
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
