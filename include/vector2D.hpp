
#include <cmath>
#include <random>
class Vector2D {
  public:
    float x = 0.0f, y = 0.0f;
    Vector2D() = default;
    Vector2D(float x, float y) : x(x), y(y) {};
    Vector2D(const Vector2D& o) = default;

    Vector2D operator*(const Vector2D& o) const { return Vector2D(x * o.x, y * o.y); };
    Vector2D operator*(const float s) const { return Vector2D(x * s, y * s); };
    Vector2D& operator*=(const Vector2D& o) {
        x *= o.x;
        y *= o.y;
        return *this;
    };
    Vector2D& operator*=(const float s) {
        x *= s;
        y *= s;
        return *this;
    };
    Vector2D operator/(const Vector2D& o) const { return Vector2D(x / o.x, y / o.y); };
    Vector2D operator/(const float s) const { return Vector2D(x / s, y / s); };
    Vector2D& operator/=(const Vector2D& o) {
        x /= o.x;
        y /= o.y;
        return *this;
    };
    Vector2D& operator/=(const float s) {
        x /= s;
        y /= s;
        return *this;
    };
    Vector2D operator+(const Vector2D& o) const { return Vector2D(x + o.x, y + o.y); }
    Vector2D operator+(const float s) const { return Vector2D(x + s, y + s); };
    Vector2D& operator+=(const Vector2D& o) {
        x += o.x;
        y += o.y;
        return *this;
    };
    Vector2D& operator+=(const float s) {
        x += s;
        y += s;
        return *this;
    };
    Vector2D operator-(const Vector2D& o) const { return Vector2D(x - o.x, y - o.y); };
    Vector2D operator-(const float s) const { return Vector2D(x - s, y - s); };
    Vector2D& operator-=(const Vector2D& o) {
        x -= o.x;
        y -= o.y;
        return *this;
    };
    Vector2D& operator-=(const float s) {
        x -= s;
        y -= s;
        return *this;
    };

    Vector2D& operator=(const Vector2D& o) = default;

    float distance(const Vector2D& o) const {
        float dx = x - o.x;
        float dy = y - o.y;
        return sqrtf(dx * dx + dy * dy);
    };
    float dot(const Vector2D& o) const { return x * o.x + y * o.y; }
    float norm() const { return sqrtf(x * x + y * y); }
    Vector2D& truncate(const float max_mag) {
        float mag = norm();
        if (mag > max_mag) {
            x *= max_mag / mag;
            y *= max_mag / mag;
        }
        return *this;
    };
    Vector2D& normalize() {
        float mag = norm();
        if (mag != 0) {
            x /= mag;
            y /= mag;
        }
        return *this;
    };
    static Vector2D Random(float minX, float maxX, float minY, float maxY) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distX(minX, maxX);
        std::uniform_real_distribution<float> distY(minY, maxY);
        return Vector2D(distX(gen), distY(gen));
    }
};
