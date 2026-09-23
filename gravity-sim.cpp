#include <iostream>
using namespace std;

// headers for OpenGL and GLFW
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// graphics library math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



struct Engine {
    GLFWwindow* window;
    int WIDTH = 640, HEIGHT = 480;

        Engine() {
            /* Initialize the library */
            if (!glfwInit()) {
                cerr << "glfw didn't start" << endl;
                exit(EXIT_FAILURE);
            }

            /* Create a windowed mode window and its OpenGL context */
            window = glfwCreateWindow(WIDTH, HEIGHT, "gravity-sim", nullptr, nullptr);
            if (!window)
            {
                cerr << "no window for you" << endl;
                glfwTerminate();
                exit(EXIT_FAILURE);
            }

            // point every future drawing command at this window
            glfwMakeContextCurrent(window);
            glewExperimental = GL_TRUE;
            glewInit();
        }

        // this runs once per frame
        void run() {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
        }
};

int main(void)
{   
    Engine engine;

    std:vector<glm::vec3> gridVertices;

    for (int z = -2; z <= 2; z++) {
        glm::vec3 start(-2.0f, 0.0f, z);
        glm::vec3 end( 2.0f, 0.0f, z);

        gridVertices.push_back(start);
        gridVertices.push_back(end);
    }

    for (int x = -2; x <= 2; x++) {
        glm::vec3 start(x, 0.0f, -2.0f);
        glm::vec3 end(x, 0.0f, 2.0f);

        gridVertices.push_back(start);
        gridVertices.push_back(end);
    }

    std::cout << gridVertices.size() << endl;

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        gridVertices.size() *sizeof(glm::vec3),
        gridVertices.data(),
        GL_STATIC_DRAW
    );

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(glm::vec3),
        (void*) 0
    );

    glEnableVertexAttribArray(0);
    

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(engine.window))
    {
        engine.run();

        /* Swap front and back buffers */
        glfwSwapBuffers(engine.window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}