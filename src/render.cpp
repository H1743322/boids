#include "render.hpp"
#include "boid.hpp"
#include <GL/gl.h>
#include <cassert>

void Render::setWindowSize(float w, float h) {
    m_width = w;
    m_height = h;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void Render::applyCameraTransform(const Camera2D& camera) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, m_width, 0.0f, m_height, -1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(m_width * 0.5f, m_height * 0.5f, 0.0f);
    glScalef(camera.zoom, camera.zoom, 1.0f);
    glTranslatef(-camera.x, -camera.y, 0.0f);
}

void Render::renderAxes(float max) {
    glPushMatrix();
    glLineWidth(1.5f);
    glBegin(GL_LINES);

    glColor3f(1.f, 0.f, 0.f);
    glVertex2f(-max, 0.f);
    glVertex2f(max, 0.f);

    glColor3f(0.f, 1.f, 0.f);
    glVertex2f(0.f, -max);
    glVertex2f(0.f, max);

    glEnd();
    glPopMatrix();
}
void Render::renderBoid(const Boid& b) {
    glPushMatrix();

    glTranslatef(b.pos.x, b.pos.y, 0.0f);

    float degrees = b.orientation * 180.0f / M_PI;
    glRotatef(degrees, 0.0f, 0.0f, 1.0f);

    glColor3f(1.0f, 1.0f, 1.0f); // White
    glBegin(GL_TRIANGLES);
    glVertex2f(10.0f, 0.0f);
    glVertex2f(-5.0f, 4.0f);
    glVertex2f(-5.0f, -4.0f);
    glEnd();

    glPopMatrix();
}
void Render::renderBounds(const float width, const float height) {
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f); // Blue
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-width / 2, -height / 2);
    glVertex2f(width / 2, -height / 2);
    glVertex2f(width / 2, height / 2);
    glVertex2f(-width / 2, height / 2);
    glEnd();
    glPopMatrix();
}
void Render::render(const Camera2D& camera, const std::vector<Boid>& boids) {
    glDisable(GL_DEPTH_TEST);
    applyCameraTransform(camera);
    // renderAxes(10'000.0f);
    for (const Boid& b : boids) {
        renderBoid(b);
    }
}
