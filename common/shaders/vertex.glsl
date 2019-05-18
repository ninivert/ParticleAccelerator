#version 330
// layout(location = 0) in vec3 position;
// layout(location = 1) in vec3 color;
in vec3 position;
out vec4 vColor;
out vec3 vNormal;

uniform vec4 color;
uniform mat4 modelToWorld;
uniform mat4 worldToCamera;
uniform mat4 cameraToView;

void main() {
	vec4 worldPosition = modelToWorld * vec4(position, 1.0);
	gl_Position = cameraToView * worldToCamera * worldPosition;
	vColor = color;
	// vColor = worldPosition;
}
