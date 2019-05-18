#version 330
// layout(location = 0) in vec3 position;
// layout(location = 1) in vec3 color;
in vec3 position;
in vec3 normal;
out vec3 vColor;
out vec3 vNormal;
out vec3 vFragPos;

uniform vec3 color;
uniform mat4 modelToWorld;
uniform mat4 worldToCamera;
uniform mat4 cameraToView;

void main() {
	vec4 worldPosition = modelToWorld * vec4(position, 1.0);
	gl_Position = cameraToView * worldToCamera * worldPosition;
	vColor = color;
	vNormal = normal;
	vFragPos = vec3(worldPosition);
	// activate for funky shader
	// vColor = vec3(worldPosition);
}
