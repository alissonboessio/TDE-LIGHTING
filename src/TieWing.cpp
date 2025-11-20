#include "TieWing.h"

TieWing::TieWing(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl)
    : Object(pos, rot, scl) {
    init();
}

void TieWing::init() {

    // Formato: Posição(x,y,z), Normal(nx,ny,nz), Textura(u,v)
    float vertices2[] = {
        // --- FACE ESQUERDA (X=0) ---
        // Normal aponta para -X (-1.0, 0.0, 0.0)
        0.0f, 0.0f, -0.6f,  -1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // A
        0.0f, 0.5f, -0.3f,  -1.0f, 0.0f, 0.0f,  0.0f, 1.0f, // C
        0.0f, 0.0f,  0.0f,  -1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // G

        0.0f, 0.5f, -0.3f,  -1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // C
        0.0f, 0.5f,  0.3f,  -1.0f, 0.0f, 0.0f,  0.0f, 1.0f, // D
        0.0f, 0.0f,  0.0f,  -1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // G

        0.0f, 0.5f,  0.3f,  -1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // D
        0.0f, 0.0f,  0.6f,  -1.0f, 0.0f, 0.0f,  0.0f, 1.0f, // B
        0.0f, 0.0f,  0.0f,  -1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // G

        0.0f, 0.0f,  0.6f,  -1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // B
        0.0f, -0.5f, 0.3f,  -1.0f, 0.0f, 0.0f,  0.0f, 1.0f, // F
        0.0f, 0.0f,  0.0f,  -1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // G

        0.0f, -0.5f,  0.3f, -1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // F
        0.0f, -0.5f, -0.3f, -1.0f, 0.0f, 0.0f,  0.0f, 1.0f, // E
        0.0f, 0.0f,   0.0f, -1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // G

        0.0f, -0.5f, -0.3f, -1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // E
        0.0f, 0.0f, -0.6f,  -1.0f, 0.0f, 0.0f,  0.0f, 1.0f, // A
        0.0f, 0.0f,   0.0f, -1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // G

        // --- FACE DIREITA (X=0.1) ---
        // Normal aponta para +X (1.0, 0.0, 0.0)
        0.1f, 0.0f, -0.6f,  1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // A1
        0.1f, 0.5f, -0.3f,  1.0f, 0.0f, 0.0f,   0.0f, 1.0f, // C1
        0.1f, 0.0f,  0.0f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // G1

        0.1f, 0.5f, -0.3f,  1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // C1
        0.1f, 0.5f,  0.3f,  1.0f, 0.0f, 0.0f,   0.0f, 1.0f, // D1
        0.1f, 0.0f,  0.0f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // G1

        0.1f, 0.5f,  0.3f,  1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // D1
        0.1f, 0.0f,  0.6f,  1.0f, 0.0f, 0.0f,   0.0f, 1.0f, // B1
        0.1f, 0.0f,  0.0f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // G1

        0.1f, 0.0f,  0.6f,  1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // B1
        0.1f, -0.5f, 0.3f,  1.0f, 0.0f, 0.0f,   0.0f, 1.0f, // F1
        0.1f, 0.0f,  0.0f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // G1

        0.1f, -0.5f,  0.3f, 1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // F1
        0.1f, -0.5f, -0.3f, 1.0f, 0.0f, 0.0f,   0.0f, 1.0f, // E1
        0.1f, 0.0f,   0.0f, 1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // G1

        0.1f, -0.5f, -0.3f, 1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // E1
        0.1f, 0.0f,  -0.6f, 1.0f, 0.0f, 0.0f,   0.0f, 1.0f, // A1
        0.1f, 0.0f,   0.0f, 1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // G1

        // --- BORDAS LATERAIS ---

        // Borda Superior-Traseira (A-C): Inclinada para cima e para trás
        // Normal aprox: (0.0, 0.51, -0.86)
        0.0f, 0.0f, -0.6f,  0.0f, 0.51f, -0.86f,  1.0f, 1.0f,
        0.1f, 0.0f, -0.6f,  0.0f, 0.51f, -0.86f,  1.0f, 0.0f,
        0.1f, 0.5f, -0.3f,  0.0f, 0.51f, -0.86f,  0.0f, 0.0f,
        0.1f, 0.5f, -0.3f,  0.0f, 0.51f, -0.86f,  1.0f, 1.0f,
        0.0f, 0.5f, -0.3f,  0.0f, 0.51f, -0.86f,  1.0f, 0.0f,
        0.0f, 0.0f, -0.6f,  0.0f, 0.51f, -0.86f,  0.0f, 0.0f,

        // Borda Superior (C-D): Totalmente Horizontal, aponta para Cima
        // Normal: (0.0, 1.0, 0.0)
        0.0f, 0.5f, -0.3f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
        0.1f, 0.5f, -0.3f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        0.1f, 0.5f,  0.3f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
        0.1f, 0.5f,  0.3f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
        0.0f, 0.5f,  0.3f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        0.0f, 0.5f, -0.3f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,

        // Borda Frontal (D-B): Inclinada para frente e para baixo
        // Normal aprox: (0.0, 0.51, 0.86)
        0.0f, 0.5f,  0.3f,  0.0f, 0.51f, 0.86f,  1.0f, 1.0f,
        0.1f, 0.5f,  0.3f,  0.0f, 0.51f, 0.86f,  1.0f, 0.0f,
        0.1f, 0.0f,  0.6f,  0.0f, 0.51f, 0.86f,  0.0f, 0.0f,
        0.1f, 0.0f,  0.6f,  0.0f, 0.51f, 0.86f,  1.0f, 1.0f,
        0.0f, 0.0f,  0.6f,  0.0f, 0.51f, 0.86f,  1.0f, 0.0f,
        0.0f, 0.5f,  0.3f,  0.0f, 0.51f, 0.86f,  0.0f, 0.0f,

        // Borda Inferior-Frontal (B-F): Inclinada para baixo e para trás
        // Normal aprox: (0.0, -0.51, 0.86)
        0.0f, 0.0f,  0.6f,  0.0f, -0.51f, 0.86f,  1.0f, 1.0f,
        0.1f, 0.0f,  0.6f,  0.0f, -0.51f, 0.86f,  1.0f, 0.0f,
        0.1f, -0.5f, 0.3f,  0.0f, -0.51f, 0.86f,  0.0f, 0.0f,
        0.1f, -0.5f, 0.3f,  0.0f, -0.51f, 0.86f,  1.0f, 1.0f,
        0.0f, -0.5f, 0.3f,  0.0f, -0.51f, 0.86f,  1.0f, 0.0f,
        0.0f, 0.0f,  0.6f,  0.0f, -0.51f, 0.86f,  0.0f, 0.0f,

        // Borda Inferior (F-E): Totalmente Horizontal, aponta para Baixo
        // Normal: (0.0, -1.0, 0.0)
        0.0f, -0.5f, 0.3f,  0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
        0.1f, -0.5f, 0.3f,  0.0f, -1.0f, 0.0f,  1.0f, 1.0f,
        0.1f, -0.5f, -0.3f, 0.0f, -1.0f, 0.0f,  0.0f, 1.0f,
        0.1f, -0.5f, -0.3f, 0.0f, -1.0f, 0.0f,  0.0f, 1.0f,
        0.0f, -0.5f, -0.3f, 0.0f, -1.0f, 0.0f,  0.0f, 1.0f,
        0.0f, -0.5f, 0.3f,  0.0f, -1.0f, 0.0f,  1.0f, 0.0f,

        // Borda Traseira (E-A): Inclinada para cima e para trás (lado de baixo)
        // Normal aprox: (0.0, -0.51, -0.86)
        0.0f, -0.5f, -0.3f, 0.0f, -0.51f, -0.86f,  1.0f, 1.0f,
        0.1f, -0.5f, -0.3f, 0.0f, -0.51f, -0.86f,  1.0f, 0.0f,
        0.1f, 0.0f, -0.6f,  0.0f, -0.51f, -0.86f,  0.0f, 0.0f,
        0.1f, 0.0f, -0.6f,  0.0f, -0.51f, -0.86f,  1.0f, 1.0f,
        0.0f, 0.0f, -0.6f,  0.0f, -0.51f, -0.86f,  1.0f, 0.0f,
        0.0f, -0.5f, -0.3f, 0.0f, -0.51f, -0.86f,  0.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // EBO não é usado com glDrawArrays nesta configuração, removi para simplificar
    // Se quiser manter, pode, mas o vertices2 acima é para desenhar direto.

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    // Agora temos 8 floats por vértice (3 pos + 3 normal + 2 tex)
    int stride = 8 * sizeof(float);

    // 1. Posição (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    // 2. Normal (location = 1) - Começa no float índice 3
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 3. Textura (location = 2) - Começa no float índice 6
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void TieWing::draw(Shader &shader, glm::mat4 model) {

    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    shader.setMat4("model", model);

    glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 72);
    glBindVertexArray(0);
}
