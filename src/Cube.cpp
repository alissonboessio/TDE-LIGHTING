// Cube.cpp
#include "Cube.h"

Cube::Cube(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang)
    : Object(pos,rot, scl), angle(ang) {
    init();
}

void Cube::init() {

    float vertices[] = {
        // positions          // normals           // tex coords
        // back face (z = -0.5) normal (0,0,-1)
       -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   1.0f, 0.0f,
       -0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   0.0f, 0.0f,

        // front face (z = +0.5) normal (0,0,1)
       -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
       -0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   0.0f, 1.0f,

        // left face (x = -0.5) normal (-1,0,0)
       -0.5f, -0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
       -0.5f,  0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
       -0.5f,  0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
       -0.5f, -0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,

        // right face (x = +0.5) normal (1,0,0)
        0.5f, -0.5f, -0.5f,    1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,    1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,    1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,    1.0f,  0.0f,  0.0f,   1.0f, 1.0f,

        // top face (y = +0.5) normal (0,1,0)
       -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,   0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,   1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
       -0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,   0.0f, 0.0f,

        // bottom face (y = -0.5) normal (0,-1,0)
       -0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,   0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,   1.0f, 1.0f,
       -0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,   0.0f, 1.0f
    };

    unsigned int indices[] = {
        0,1,2,  2,3,0,       // back
        4,5,6,  6,7,4,       // front
        8,9,10, 10,11,8,     // left
        12,13,14,14,15,12,   // right
        16,17,18,18,19,16,   // top
        20,21,22,22,23,20    // bottom
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // posição (location 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // normal (location 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // tex coords (location 2)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}


void Cube::draw(Shader &shader, glm::mat4 model) {

    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    model = glm::rotate(model, glm::radians(angle), rotation);

    shader.setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
