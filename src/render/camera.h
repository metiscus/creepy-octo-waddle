#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "../global.h"

class Camera
{
public:
    Camera();
    void SetOrthographic(float left, float right, float bottom, float top, float zNear, float zFar);
    void SetView(glm::vec3 eye, glm::vec3 center, glm::vec3 up);

    const glm::mat4& GetProjectionMatrix() const;
    const glm::mat4& GetViewMatrix() const;

private:
    glm::mat4 projection_;
    glm::mat4 view_;
};

#endif /* CAMERA_H_INCLUDED */
