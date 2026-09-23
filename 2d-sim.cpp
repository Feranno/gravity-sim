#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

struct Engine {
    GLFWwindow* window;
    int WIDTH = 800, HEIGHT = 600;

    Engine() {
        // wake up GLFW
        if (!glfwInit()) {
            cerr << "glfw didn't start" << endl;
            exit(EXIT_FAILURE);
        }

        // ask the operating system for a window
        window = glfwCreateWindow(WIDTH, HEIGHT, "2d-gravity-sim", nullptr, nullptr);
        if (!window) {
            cerr << "no window for you" << endl;
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        // point every future drawing command at this window
        glfwMakeContextCurrent(window);
        glewInit();

        int fbWidth, fbHeight;
        glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
        glViewport(0, 0, fbWidth, fbHeight);
    }

    // this runs once per frame
    void run() {
        // wipe the screen to almost-black
        glClearColor(0.05f, 0.05f, 0.08f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // put (0, 0) in the middle instead of the corner
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-WIDTH / 2.0, WIDTH / 2.0, -HEIGHT / 2.0, HEIGHT / 2.0, -1.0, 1.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
};

void drawCircle(float cx, float cy, float r, float cr, float cg, float cb) {
    // every point on the circle
    const double pi = 3.14159265358979323846;
    double radians = 360 * (pi / 180.0);

    for (int iterations = 1; iterations < 360; iterations++) {
        double increment = (360.0 / static_cast<double>(iterations)) * (pi / 180.0);
        glColor3f(cr, cg, cb);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        glVertex2f(cx + r*cos(radians), cy + r*sin(radians));
        glVertex2f(cx + r*cos(radians + increment), cy + r*sin(radians + increment));
        glEnd();
        radians = radians + increment;
    }
    
    /*
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0, 0);
    glVertex2f(50, 0);
    glVertex2f(0, 50);
    glVertex2f(-50, 0);
    glEnd();
    */
}

struct Planet {
    float x, y;
    float vx, vy;
    float r;
    float m;
    float cr, cg, cb;
};

int main() {
    Engine engine;

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    float animationTime = 0.0f;
    float loopDuration = 30.0f; // The loop resets every 3 seconds


    // define planets
    std::vector<Planet> planets = {
   //    x     y    vx    vy   r     m    cr    cg    cb
    {    0,    0,  0.0,  0.0, 40, 4000, 1.00, 0.78, 0.25 }, // sun
    {  140,    0,  0.0,  4.1, 16,   20, 0.35, 0.62, 1.00 }, // earth
    { -160, -160,  2.3, -2.3, 12,   12, 0.90, 0.38, 0.24 }, // mars
    { -170,  170, -2.2, -2.2, 14,   14, 0.70, 0.55, 1.00 }, // yours
    };

    // keep running until someone closes the window
    while (!glfwWindowShouldClose(engine.window)) {
        engine.run();

        // 1. Calculate delta time
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        animationTime += deltaTime;
        
        // loop animation
        if (animationTime >= loopDuration) {
            // reset parameters 
            animationTime = 0.0f;
            planets = {
           //    x     y    vx    vy   r     m    cr    cg    cb
            {    0,    0,  0.0,  0.0, 40, 4000, 1.00, 0.78, 0.25 }, // sun
            {  140,    0,  0.0,  4.1, 16,   20, 0.35, 0.62, 1.00 }, // earth
            { -160, -160,  2.3, -2.3, 12,   12, 0.90, 0.38, 0.24 }, // mars
            { -170,  170, -2.2, -2.2, 14,   14, 0.70, 0.55, 1.00 }, // yours
            };
        }

        for (auto& p : planets) {

            float ax = 0;
            float ay = 0;
            // figuring out the ax and ay of each planet wrt all other planets
            for (auto& other : planets) {
                if (&other == &p) continue;

                // calculate the gravitation pull on planet from all other planets
                float dx = other.x - p.x;
                float dy = other.y - p.y;
                float r = sqrtf((dx * dx) + (dy * dy));

                float a = (0.6 * other.m) / ((r * r) + 25);
                ax += a * (dx / r);
                ay += a * (dy / r);
            }

            // nudge p's speed, then move p
            float time = animationTime;
            float dt = time * 0.2f;
            p.vx += ax * dt;
            p.x += p.vx * dt;
            p.vy += ay * dt;
            p.y += p.vy * dt;
            
            drawCircle(p.x, p.y, p.r, p.cr, p.cg, p.cb);

            // hits ground
            /*
            if (ray.pos <= 0) {
                ray.acc = 0;
                ray.vel = 0;
            }
            */
            
        }

        glfwSwapBuffers(engine.window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

