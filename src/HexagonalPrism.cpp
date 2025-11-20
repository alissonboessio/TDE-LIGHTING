#include "HexagonalPrism.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


HexagonalPrism::HexagonalPrism(glm::vec3 pos, float radiusTop, float radiusBottom, float height, float angle)
    : Hexagon(pos, radiusTop, height, angle), angle(angle) {
    init(radiusTop, radiusBottom, height);
}

HexagonalPrism::HexagonalPrism(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl,
                               float radiusTop, float radiusBottom, float height, float angle)
    : Hexagon(pos, rot, scl, radiusTop, height, angle), angle(angle) {
    init(radiusTop, radiusBottom, height);
}

void HexagonalPrism::init(float radiusTop, float radiusBottom, float height) {

    vertices.clear();
    indices.clear();

    int segments = 6;
    float halfH = height / 2.0f;
    float step = 2.0f * M_PI / segments;

    // --- TOPO (centro + anel) ---
    int topCenterIndex = static_cast<int>(vertices.size() / 8);
    // centro do topo
    vertices.insert(vertices.end(), {
        0.0f,  halfH, 0.0f,     // pos
        0.0f,  1.0f, 0.0f,      // normal
        0.5f,  0.5f             // tex
    });

    for (int i = 0; i <= segments; i++) {
        float theta = i * step;
        float x = radiusTop * cos(theta);
        float z = radiusTop * sin(theta);
        float u = (cos(theta) + 1.0f) * 0.5f;
        float v = (sin(theta) + 1.0f) * 0.5f;

        vertices.insert(vertices.end(), {
            x,      halfH, z,   // pos
            0.0f,   1.0f, 0.0f, // normal topo
            u,      v          // tex
        });
    }

    // --- BASE (centro + anel) ---
    int baseCenterIndex = static_cast<int>(vertices.size() / 8);
    // centro da base
    vertices.insert(vertices.end(), {
        0.0f, -halfH, 0.0f,     // pos
        0.0f,-1.0f,  0.0f,      // normal
        0.5f, 0.5f             // tex
    });

    for (int i = 0; i <= segments; i++) {
        float theta = i * step;
        float x = radiusBottom * cos(theta);
        float z = radiusBottom * sin(theta);
        float u = (cos(theta) + 1.0f) * 0.5f;
        float v = (sin(theta) + 1.0f) * 0.5f;

        vertices.insert(vertices.end(), {
            x,     -halfH, z,   // pos
            0.0f, -1.0f,  0.0f, // normal base
            u,     v           // tex
        });
    }

    // --- LATERAIS (dois vértices por segmento: topo e base) ---
    int sideStartIndex = static_cast<int>(vertices.size() / 8);
    for (int i = 0; i <= segments; i++) {
        float theta = i * step;
        float xt = radiusTop * cos(theta);
        float zt = radiusTop * sin(theta);
        float xb = radiusBottom * cos(theta);
        float zb = radiusBottom * sin(theta);

        // normal radial aproximada
        float nx = cos(theta);
        float nz = sin(theta);

        float u = 1.0f - (float)i / segments;

        // vértice topo da lateral
        vertices.insert(vertices.end(), {
            xt,  halfH, zt,    // pos
            nx,  0.0f,  nz,    // normal
            u,   1.0f          // tex
        });

        // vértice base da lateral
        vertices.insert(vertices.end(), {
            xb, -halfH, zb,    // pos
            nx,  0.0f,  nz,    // normal
            u,   0.0f          // tex
        });
    }

    // --- ÍNDICES ---

    // topo (triângulos em torno do centro)
    for (int i = 1; i <= segments; i++) {
        indices.push_back(topCenterIndex);
        indices.push_back(topCenterIndex + i);
        indices.push_back(topCenterIndex + i + 1);
    }

    // base (invertendo ordem pra normal apontar para baixo corretamente)
    for (int i = 1; i <= segments; i++) {
        indices.push_back(baseCenterIndex);
        indices.push_back(baseCenterIndex + i + 1);
        indices.push_back(baseCenterIndex + i);
    }

    // laterais (faixas entre cada par de segmentos)
    for (int i = 0; i < segments; i++) {
        int top1 = sideStartIndex + i * 2;
        int bot1 = top1 + 1;
        int top2 = top1 + 2;
        int bot2 = bot1 + 2;

        // primeiro triângulo
        indices.push_back(top1);
        indices.push_back(bot1);
        indices.push_back(top2);

        // segundo triângulo
        indices.push_back(top2);
        indices.push_back(bot1);
        indices.push_back(bot2);
    }

    // --- BUFFERS / ATTRIBS ---
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // posição (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // normal (location = 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // tex coords (location = 2)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

