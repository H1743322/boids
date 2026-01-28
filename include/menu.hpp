#pragma once
#include "boid.hpp"
#include "imgui.h"

class Menu {
  public:
    void render(BoidParams& p) {
        ImGui::Begin("Simulation");
        renderFPS();
        renderBoidsParams(p);
        ImGui::End();
    }

  private:
    void renderFPS() {
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::Separator();
    }
    void renderBoidsParams(BoidParams& params) {
        float deg = params.fov_angle_rad * 180.0f / M_PI;

        ImGui::SliderFloat("Max Force", &params.max_force, 0.0f, 1.0f);
        ImGui::SliderFloat("Max Speed", &params.max_speed, 0.0f, 15.0f);
        ImGui::SliderFloat("Separation Distance", &params.separation_dist, 0.0f, 200.0f);
        ImGui::SliderFloat("Alignment Distance", &params.alignment_dist, 0.0f, 200.0f);
        ImGui::SliderFloat("Cohesion Distance", &params.cohesion_dist, 0.0f, 200.0f);
        ImGui::SliderFloat("FOV (deg)", &deg, 0.0f, 360.0f);
        params.fov_angle_rad = deg * M_PI / 180.0f;
        ImGui::InputFloat("Width Bounds", &params.bound_w, 0.0f, 3000.0f);
        ImGui::InputFloat("Height Bounds", &params.bound_h, 0.0f, 2000.0f);
        ImGui::InputFloat("Maring Bounds", &params.bound_margin, 1.0f, 100.0f);
    }
};
