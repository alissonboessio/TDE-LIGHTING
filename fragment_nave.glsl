#version 330 core 
out vec4 FragColor; 

in vec2 TexCoord;
uniform sampler2D texture1; 
uniform sampler2D texture2; 

void main() { 

	vec4 tex = texture(texture1, TexCoord);
	if (tex.a < 0.05) 
	     discard; 
	
	FragColor = tex; 
}
