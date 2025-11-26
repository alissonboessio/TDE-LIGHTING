#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Shader.h>
#include <Application.h>
#include <Cube.h>
#include <TieFighter.h>
#include <Cylinder.h>
#include <TieWing.h>
#include <XWing.h>
#include <XWingClosed.h>
#include <Hexagon.h>
#include <Sphere.h>
#include <Texture.h>
#include <Skybox.h>
#include <Plate.h>
#include <LightSphere.h>

#include <iostream>
#include <vector>
#include <ctime>
#include <string>

int WIDTH = 1400;
int HEIGHT = 700;

//Variáveis da câmera
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  10.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
float cameraSpeed = 0.01f;


float yaw   = -90.0f; //olhando para -Z
float pitch =  0.0f;
float lastX = 1024.0f / 2.0;
float lastY = 768.0f / 2.0;
float fov   = 45.0f;

bool firstMouse = true;
bool showXWing = false;

//Luz (posição inicial e cor)
glm::vec3 lightPos   = glm::vec3(3.0f, 0.0f, 5.0f);
glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
float lightMoveSpeed = 0.01f; //velocidade de movimento da luz

void resetPosic() {
    cameraPos   = glm::vec3(0.0f, 0.0f,  10.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    yaw   = -90.0f;
    pitch =  0.0f;
    lightPos   = glm::vec3(3.0f, 0.0f, 5.0f);
    lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) { // evitar salto inicial
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = static_cast<float>(xpos - lastX);
    float yoffset = static_cast<float>(lastY - ypos); // invertido
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)  pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

    //Movimento da câmera
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPos += cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPos -= cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) //sobe
            cameraPos += cameraSpeed * cameraUp;
        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) //desce
            cameraPos -= cameraSpeed * cameraUp;
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            resetPosic();

        //Mostrar/remover XWing do piloto
        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
            showXWing = true;
        if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
            showXWing = false;

        //Movimento da luz
        //E/P -> eixo X
        if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
            lightPos.x += lightMoveSpeed;    //aumenta X
        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
            lightPos.x -= lightMoveSpeed;    //diminui X

        //K/L -> eixo Y
        if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
            lightPos.y += lightMoveSpeed;    //aumenta Y (sobe)
        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
            lightPos.y -= lightMoveSpeed;    //diminui Y (desce)

        //N/M -> eixo Z
        if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
            lightPos.z += lightMoveSpeed;    //aumenta Z
        if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
            lightPos.z -= lightMoveSpeed;    //diminui Z

}

int main() {
    //Cria janela e inicializa OpenGL
    Application app(WIDTH, HEIGHT, "GLFW Star Wars Tie Fighter");
    if (!app.init()) return -1;

    glfwSetInputMode(app.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(app.getWindow(), mouse_callback);

    //Carrega shader principal (vertex/fragment com iluminação)
    Shader shader("vertex.glsl", "fragment.glsl");
    shader.use();

    shader.setFloat("ambientStrength", 0.15f);
    shader.setFloat("diffuseStrength", 1.0f);
    shader.setFloat("specularStrength", 0.4f);


    //Shader do cubo da luz (apenas posição, sem iluminação)
    Shader lightCubeShader("light_cube.vs", "light_cube.fs");

    //Carrega texturas
    Texture tex1("imagens/Tie23.png");
    Texture tex2("imagens/Alpha.png");        //logo em branco
    Texture tex3("imagens/star_wars.png");    //logo OpenGL com alpha
    Texture tex4("imagens/DeathStar4.png");
    Texture tex5("imagens/DeathStar3.png");
    Texture tex6("imagens/xwing.png");
    Texture tex7("imagens/madeira.jpg");
    Texture tex8("imagens/star_wars3.png");
    Texture tex9("imagens/pedra-28.jpg");
    Texture tex10("imagens/folhas.jpg");

    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);

    // --- Inicializa e posiciona objetos em cena ---

    Sphere ob1 = Sphere(glm::vec3(0.0f, 0.0f, 0.0f));
    ob1.scale = glm::vec3(2.5f, 2.5f, 2.5f);

    XWing ob2 = XWing(glm::vec3(0.0f, 6.0f, 0.5f),
                      glm::vec3(0.0f, 0.0f, 1.0f),
                      glm::vec3(0.3f, 0.3f, 0.3f),
                      0.0f);
    ob2.scale = glm::vec3(0.5f);

    XWing ob6 = XWing(glm::vec3(0.5f, 4.0f, 0.6f),
                      glm::vec3(0.0f, 0.0f, 1.0f),
                      glm::vec3(0.3f, 0.3f, 0.3f),
                      0.0f);
    ob6.scale = glm::vec3(0.5f);

    XWingClosed ob8 = XWingClosed(glm::vec3(3.5f, 2.0f, 0.6f),
                                  glm::vec3(1.0f, 0.0f, 0.0f),
                                  glm::vec3(0.3f, 0.3f, 0.3f),
                                  0.0f);
    ob8.scale = glm::vec3(0.5f);

    TieFighter ob3(glm::vec3(2.0f, 0.0f, -2.5f));
    TieFighter ob4(glm::vec3(-2.0f, 1.0f, -4.0f));
    TieFighter ob5(glm::vec3(-3.0f, 0.0f, 0.0f));
    TieFighter ob7(glm::vec3(-5.0f, -0.2f, 0.0f));

    glm::vec3 scale = glm::vec3(0.9f);

    Cube cube(glm::vec3(-4.0f, -0.1f, 2.5f));
    cube.scale = scale;

    Sphere sphere(glm::vec3(-4.0f, -0.1f, -1.5f));
    sphere.scale = scale;

    Cylinder cylinder(glm::vec3(-4.0f, -0.1f, -2.5f),
                      glm::vec3(1.0f, 0.0f, 0.0f),
                      glm::vec3(1.0f, 1.0f, 1.0f),
                      0.5f, 1.0f, 36, 90.0f);
    cylinder.scale = scale;

    Hexagon hexagon(glm::vec3(-4.0f, -0.1f, -4.5f), 0.5f, 1.0f, 90.0f);
    hexagon.rotation = glm::vec3(0.0f, 0.0f, 1.0f);
    hexagon.scale = scale;

    ob3.scale = scale;
    ob4.scale = scale;
    ob5.scale = scale;
    ob7.scale = scale;

    XWing ob9 = XWing(glm::vec3(-2.0f, 1.0f, -4.0f),
                      glm::vec3(0.0f, 0.0f, 1.0f),
                      glm::vec3(1.0f, 1.0f, 1.0f),
                      -15.0f);

    glm::vec3 pilot = glm::vec3(-0.3f, -0.05f, 10.5f);
    XWing ob10 = XWing(pilot,
                       glm::vec3(0.0f, 1.0f, 0.0f),
                       glm::vec3(1.0f, 1.0f, 1.0f),
                       0.0f);

    //Inicializa espaço sideral (skybox)
    Skybox skybox;

    LightSphere lightSphere(lightPos, 0.1f);

    //Ativa depth test
    glEnable(GL_DEPTH_TEST);

    //Loop principal
    while (!glfwWindowShouldClose(app.getWindow())) {

        //Processa input da janela
        GLFWwindow* window = app.getWindow();

        processInput(window);

        //Limpa tela e depth buffer
        glClearColor(0.02f, 0.02f, 0.05f, 1.0f); //fundo mais escuro
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        //Configura view e projection
        glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                               ((float) WIDTH / (float) HEIGHT),
                                               0.1f, 100.0f);

        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        //a skybox só precisa da rotação da câmera, não da posição
        glm::mat4 skyboxView = glm::mat4(glm::mat3(view));

        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        //Envia parâmetros de iluminação (inclui a nova posição da luz)
        shader.setVec3("lightPos",   lightPos);
        shader.setVec3("lightColor", lightColor);
        shader.setVec3("viewPos",    cameraPos);

        glm::mat4 model = glm::mat4(1.0f);
        float angle = 20.0f;
        model = glm::rotate(model,
                            (angle * (float) glfwGetTime()) / 80.0f,
                            glm::vec3(0.0f, 0.3f, 0.0f));
        shader.setMat4("model", model);

        //Troca textura para estrela da morte
        tex4.bind(0);
        tex5.bind(1);
        ob1.draw(shader, model);

        //Troca textura para Tie-fighters (caças imperiais)
        tex1.bind(0);
        tex2.bind(1);

        model = glm::rotate(model,
                            (angle * (float) glfwGetTime()) / 5.0f,
                            glm::vec3(1.5f, 4.2f, 0.1f));
        shader.setMat4("model", model);
        ob3.draw(shader, model);

        model = glm::rotate(model,
                            (angle * (float) glfwGetTime()) / 40.0f,
                            glm::vec3(-0.5f, -0.2f, 1.45f));
        shader.setMat4("model", model);
        ob4.draw(shader, model);

        model = glm::mat4(1.0f);
        model = glm::rotate(model,
                            (angle * (float) glfwGetTime()) / 30.0f,
                            glm::vec3(-0.1f, 0.5f, 0.0f));

        ob5.draw(shader, model);
        ob7.draw(shader, model);

        //Troca textura para X-Wings (caças rebeldes)
        tex4.bind(0);
        tex6.bind(1);

        model = glm::mat4(1.0f);
        model = glm::rotate(model,
                            (angle * (float) glfwGetTime()) / 15.0f,
                            glm::vec3(-1.0f, 0.0f, -0.1f));
        ob8.draw(shader, model);

        model = glm::mat4(1.0f);
        model = glm::rotate(model,
                            (angle * (float) glfwGetTime()) / 15.0f,
                            glm::vec3(-1.0f, 1.0f, -0.1f));
        ob2.draw(shader, model);
        ob6.draw(shader, model);

        if (showXWing) {
            model = glm::mat4(1.0f);
            ob10.draw(shader, model);
        }

        model = glm::mat4(1.0f);
        model = glm::rotate(model,
                            (angle * (float) glfwGetTime()) / 30.0f,
                            glm::vec3(-0.1f, 0.5f, 0.0f));

        //Troca textura para outros objetos aleatórios
        tex10.bind(0);
        tex3.bind(1);
        cube.draw(shader, model);

        tex7.bind(0);
        tex8.bind(1);
        sphere.draw(shader, model);

        cylinder.draw(shader, model);

        tex9.bind(0);
        hexagon.draw(shader, model);

        //Luz
        lightCubeShader.use();
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);

        lightSphere.position = lightPos;
        lightSphere.draw(lightCubeShader);

        //desenha a skybox
        skybox.draw(skyboxView, projection);

        //Swap buffers e eventos
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
