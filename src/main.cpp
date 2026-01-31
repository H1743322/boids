#include <glad/glad.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "input.hpp"
#include "menu.hpp"
#include "render.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

constexpr float WIDTH = 1440;
constexpr float HEIGHT = 900;
constexpr float BOIDS_COUNT = 500;

// void framebuffer_size_callback(GLFWwindow *window, int width, int height) { glViewport(0, 0, width,
// height); }

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to init GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Boids", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    // ImGui init
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    Camera2D camera;
    Render render{};
    Menu menu;

    // Build Boids
    std::vector<Boid> boids;
    BoidParams p;
    p.bound_w = WIDTH;
    p.bound_h = HEIGHT;

    for (int i = 0; i < BOIDS_COUNT; ++i) {
        Boid b;
        b.pos = Vector2D::Random(-WIDTH / 2, WIDTH / 2, -HEIGHT / 2, HEIGHT / 2);
        b.vel = Vector2D::Random(-p.max_speed, p.max_speed, -p.max_speed, p.max_speed);
        b.orientation = std::atan2(b.vel.y, b.vel.x);
        boids.push_back(b);
    }
    render.setWindowSize(WIDTH, HEIGHT);

    glfwSetWindowUserPointer(window, &camera);
    glfwSetScrollCallback(window, scrollCallback);

    float lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        glfwPollEvents();
        handleCameraInput(camera, window, deltaTime);
        handleMouseCamera(camera, window);

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Render scene
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render boids
        render.render(camera, boids);
        render.renderBounds(p.bound_w, p.bound_h);

        // Simulate
        for (Boid& b : boids) {
            b.Update(boids, p);
        }

        // Render imgui
        menu.render(p);
        ImGui::Render();

        // Render ImGui
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
