#ifndef LIGHT_SPHERE_H
#define LIGHT_SPHERE_H

#include "Sphere.h"

class LightSphere : public Sphere
{
public:
    LightSphere(glm::vec3 pos, float radius = 0.2f, int sectors = 24, int stacks = 16);

    void draw(Shader& shader, glm::mat4 model = glm::mat4(1.0f)) override;
};

#endif
