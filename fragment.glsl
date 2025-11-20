#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

//luz e câmera
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

//quanto a segunda textura influencia
uniform float mixFactor = 0.5;

void main()
{
    //cor base do material (combinando as 2 texturas)
    vec4 texColor1 = texture(texture1, TexCoord);
    vec4 texColor2 = texture(texture2, TexCoord);
    vec3 objectColor = mix(texColor1, texColor2, mixFactor).rgb;

    //componente ambiente
    float ambientStrength = 0.15;
    vec3 ambient = ambientStrength * lightColor;

    //componente difusa
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    //componente especular
    float specularStrength = 0.4;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 lighting = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(lighting, 1.0);
}
