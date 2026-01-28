#include "boid.hpp"

void Boid::Update(const std::vector<Boid>& boids, const BoidParams& p) {

    Vector2D sep = Separation(boids, p);
    Vector2D alig = Aligment(boids, p);
    Vector2D col = Cohesion(boids, p);
    Vector2D in_bounds = StayInBounds(p);

    Vector2D steering_force = sep + alig + col + in_bounds;
    steering_force.truncate(p.max_force);

    auto acc = steering_force / mass;

    vel += acc;
    vel.truncate(p.max_speed);

    pos += vel;

    if (vel.norm() > EPSILON)
        orientation = std::atan2(vel.y, vel.x);
}

Vector2D Boid::Separation(const std::vector<Boid>& boids, const BoidParams& p) {

    Vector2D steer;
    int count = 0;

    for (const Boid& b : boids) {
        if (!IsNearby(b, p.separation_dist, p.fov_angle_rad))
            continue;

        auto dist = pos.distance(b.pos);
        Vector2D diff = pos - b.pos;
        diff /= dist;
        steer += diff;
        count++;
    }

    if (count > 0) {
        steer = steer / float(count);
    }

    if (steer.norm() > 0) {
        steer.normalize();
        steer *= p.max_speed;
        steer -= vel;
        steer.truncate(p.max_force);
    }

    return steer;
}
Vector2D Boid::Aligment(const std::vector<Boid>& boids, const BoidParams& p) {

    Vector2D steer;
    Vector2D avg_vel;
    int count = 0;

    for (const Boid& b : boids) {
        if (!IsNearby(b, p.alignment_dist, p.fov_angle_rad))
            continue;

        avg_vel += b.vel;
        count++;
    }

    if (count > 0) {
        avg_vel = avg_vel / float(count);
        avg_vel.normalize();
        avg_vel *= p.max_speed;
        steer = avg_vel - vel;
        steer.truncate(p.max_force);
    }

    return steer;
}
Vector2D Boid::Cohesion(const std::vector<Boid>& boids, const BoidParams& p) {
    Vector2D center;
    Vector2D steer;
    int count = 0;

    for (const auto& b : boids) {
        if (!IsNearby(b, p.cohesion_dist, p.fov_angle_rad))
            continue;
        center += b.pos;
        count++;
    }

    if (count > 0) {
        center = center / float(count);
        center -= pos;
        center.normalize();
        center *= p.max_speed;
        steer = center - vel;
        steer.truncate(p.max_force);
    }

    return steer;
}
Vector2D Boid::StayInBounds(const BoidParams& p) {
    Vector2D steer;

    // X
    if (pos.x < -p.bound_w / 2 + p.bound_margin) {
        float scale = (-p.bound_w / 2 + p.bound_margin - pos.x) / p.bound_margin;
        steer.x += p.max_force * scale;
    } else if (pos.x > p.bound_w / 2 - p.bound_margin) {
        float scale = (pos.x - (p.bound_w / 2 - p.bound_margin)) / p.bound_margin;
        steer.x -= p.max_force * scale;
    }

    // Y
    if (pos.y < -p.bound_h / 2 + p.bound_margin) {
        float scale = (-p.bound_h / 2 + p.bound_margin - pos.y) / p.bound_margin;
        steer.y += p.max_force * scale;
    } else if (pos.y > p.bound_w / 2 - p.bound_margin) {
        float scale = (pos.y - (p.bound_h / 2 - p.bound_margin)) / p.bound_margin;
        steer.y -= p.max_force * scale;
    }

    steer.truncate(p.max_force);
    return steer;
}
bool Boid::IsNearby(const Boid& b, const float max_dist, const float fov_rad) const {
    if (&b == this) {
        return false;
    }
    Vector2D diff = pos - b.pos;
    auto dist = diff.norm();
    if (dist > max_dist) {
        return false;
    }
    Vector2D forward{std::cos(orientation), std::sin(orientation)};
    diff.normalize();
    float prod = forward.dot(diff);
    float angle = std::acos(prod);
    return angle <= fov_rad / 2.0f;
}
