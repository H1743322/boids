#pragma once
#include "boid.hpp"
#include "camera.hpp"

class Render {
  public:
    void setWindowSize(float width, float height);

    void render(const Camera2D& camera, const std::vector<Boid>& boids);
    void renderBounds(const float width, const float height);

  private:
    float m_width = 0.0f;
    float m_height = 0.0f;

    void applyCameraTransform(const Camera2D& camera);
    void renderAxes(float extent);
    void renderBoid(const Boid& b);
};
