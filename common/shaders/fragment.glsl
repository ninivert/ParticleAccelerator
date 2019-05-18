#version 330
in highp vec3 vColor;
in highp vec3 vNormal;
in highp vec3 vFragPos;
out highp vec4 fColor;

void main() {
	vec3 lightPos = vec3(0.0, 50.0, 0.0);
	vec3 lightColor = vec3(1.0, 1.0, 1.0);

	float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(vNormal);
	vec3 lightDir = normalize(lightPos - vFragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	vec3 result = (ambient + diffuse) * vColor;

	fColor = vec4(result, 1.0);
}
