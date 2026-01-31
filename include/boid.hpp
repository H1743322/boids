#pragma once

#include "vector2D.hpp"
#include <vector>

const float EPSILON = 1e-6f;

struct BoidParams {
    float max_force = .1f;
    float max_speed = 2.0f;
    float separation_dist = 100.0f;
    float alignment_dist = 150.0f;
    float cohesion_dist = 100.0f;
    float fov_angle_rad = 3.0f / 2.0f * M_PI; // 270
    float bound_w = 1440;
    float bound_h = 900;
    float bound_margin = 20;
};
class Boid {
  public:
    float mass = 1.0f;
    Vector2D pos;
    Vector2D vel{.1, .1};
    float orientation = 0.0f;

    Boid() = default;
    Vector2D Separation(const std::vector<Boid>& boids, const BoidParams& p);
    Vector2D Aligment(const std::vector<Boid>& boids, const BoidParams& p);
    Vector2D Cohesion(const std::vector<Boid>& boids, const BoidParams& p);
    void Update(const std::vector<Boid>& boids, const BoidParams& p);
    void StayInBounds(float width, float height, float max_force);
    Vector2D StayInBounds(const BoidParams& p);
    bool IsNearby(const Boid& b, const float max_dist, const float fov_rad) const;
    float angle() const;
};
