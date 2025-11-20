#include "LightSphere.h"
#include <glm/gtc/matrix_transform.hpp>

LightSphere::LightSphere(glm::vec3 pos, float radius, int sectors, int stacks)
    : Sphere(pos, radius, sectors, stacks)
{
}

void LightSphere::draw(Shader& shader, glm::mat4 model)
{
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    shader.setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
