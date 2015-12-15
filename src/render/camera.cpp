#include "camera.h"

Camera::Camera()
{
    // the user expects y to be up
    SetView(
    	glm::vec3(0., 0., 0.0f), 
    	glm::vec3(0., 0., -1.f),
        glm::vec3(0., 1., 0.f)
    );

    SetOrthographic(-400.0, 400.0, -300.0, 300.0, 0.1, 10.0);
}

void Camera::SetOrthographic(float left, float right, float bottom, float top,
                             float zNear, float zFar)
{
    projection_ = glm::ortho(left, right, bottom, top, zNear, zFar);
}

void Camera::SetView(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
    view_ = glm::lookAt(eye, center, up);
}

const glm::mat4 &Camera::GetProjectionMatrix() const
{
    return projection_;
}

const glm::mat4 &Camera::GetViewMatrix() const
{
    return view_;
}
