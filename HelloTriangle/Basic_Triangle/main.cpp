
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#define glfw_Window_Name "LearnOpenGL"
#define glfw_Window_width 800
#define glfw_Window_height 600

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

//GLSL CODE VERTEX SHADER
const char* vertexShaderSource =
"#version 330 core \n"
"layout (location =0)  in vec3 apos ;\n"
"void main ()\n"
"{\n"
"  gl_Position = vec4(apos.x ,apos.y ,apos.z ,1.0);\n"
"}";

//GLSL CODE FRAGMENT SHADER
const char* fragmentShaderSource =
"#version 330 core \n"
"out vec4 FragColor ;\n"
"void main ()\n"
"{\n"
"  FragColor = vec4(0.9 ,0.9 ,0.6 ,1.0);\n"
"}";


int main()
{
  // glfw: initialize and configure
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // glfw window creation
  GLFWwindow *window = glfwCreateWindow(glfw_Window_width, glfw_Window_height, glfw_Window_Name, NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return 0;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glad: load all OpenGL function pointers
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  //vetex Data  "only 3 3D cordinate for a Triangle"
  float vertices[] = {
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f, 0.5f, 0.0f};
  //vertix buffer object`s ID to can access the object (geniral attude when we generate any OpenGL Object)
  unsigned VBO ;
  // Generate a generic buffer
  glGenBuffers(1,&VBO);
  //spicify the type of the buffer _ or spicify the kind of data will saved here (can contain vertices)
  //set the VBO  buffer as the current buffer of this certain type 
  ///////glBindBuffer(GL_ARRAY_BUFFER , VBO);

  // copy the data from our contenar to the glbuffer 
  //telling the gl how we will use this data (freq of read & write) so he choose a sotable type of memory to store in
  //GL_STATIC_DRAW--> set(write) only once and used(read) many
  /////////glBufferData(GL_ARRAY_BUFFER , sizeof(vertices) , vertices , GL_STATIC_DRAW);


//CREATING A SHADER OBJECT AND SAVE THE REF ID IN UNSIGN INT TO CAN ACCESS THE OBJECT AS USUAL
unsigned int vertexShader ;
vertexShader = glCreateShader(GL_VERTEX_SHADER);
//ATTACH THE SOURCE CODE TO THE VERTEX SHADER OBJECT AND THEN COMPILE
glShaderSource(vertexShader ,1, &vertexShaderSource , NULL);
glCompileShader(vertexShader);

/********CHECK IF THE COMPILATION DONE RIGHT WITHOUT ANY ERRORS********/
int success ; // =0 IF COMPILATION FAILED
char infoLog[512]; // STORAGE CONTANER FOR THE ERROR MASSAGE _ TO DISPLAY IT AND KNOW THE ERROR TO FIX IT
glGetShaderiv (vertexShader ,GL_COMPILE_STATUS ,&success);
if(!success)
{
  glGetShaderInfoLog(vertexShader ,512 ,NULL ,infoLog);
  std::cout << "ERROR::SHADER::VERTEX::COMPILATION" << infoLog << std::endl ;
}

//SET UP FRAGMENT SHADER SAME AS VERTEX SHADER

//CREATE
unsigned int fragmentShader ;
fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//ATTACH SOURCE CODE & COMILE
glShaderSource(fragmentShader ,1, &fragmentShaderSource , NULL);
glCompileShader(fragmentShader);
/*CHECK*/
//use same success & infoLog contaner
glGetShaderiv (fragmentShader ,GL_COMPILE_STATUS ,&success);
if(!success)
{
  glGetShaderInfoLog(fragmentShader ,512 ,NULL ,infoLog);
  std::cout << "ERROR::SHADER::VERTEX::COMPILATION" << infoLog << std::endl ;
}

//Program Shader 
unsigned int shaderProgram ;
shaderProgram = glCreateProgram();

glAttachShader(shaderProgram , vertexShader);
glAttachShader(shaderProgram , fragmentShader);
glLinkProgram(shaderProgram);

glGetProgramiv(shaderProgram , GL_LINK_STATUS , &success );
if(!success)
{
  glGetProgramInfoLog(shaderProgram , 512 , NULL,infoLog);
  std::cout<< "ERROR::SHADER::PROGRAM::LINKING" << infoLog << std::endl ;
}
glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);  
//glUseProgram(shaderProgram);

unsigned int VAO;
glGenVertexArrays(1 , &VAO);

glBindVertexArray(VAO);

glBindBuffer(GL_ARRAY_BUFFER , VBO);
glBufferData(GL_ARRAY_BUFFER , sizeof(vertices) , vertices , GL_STATIC_DRAW);

glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 3 *sizeof(float) , (void *) 0);
glEnableVertexAttribArray(0);

glBindVertexArray(0);

  // render loop
  while (!glfwWindowShouldClose(window))
  {
    // input
    processInput(window);

    // rendering commands here
    glClearColor(0.5f, 0.3f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);


    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // glfw: terminate, clearing all previously allocated GLFW resources.
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