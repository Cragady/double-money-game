#version 100

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Custom Input Uniforms
uniform vec3 camPos;
uniform vec3 camDir;
uniform vec2 screenCenter;

// Lighting direction uniform (controls the direction of the light)
uniform vec3 lightDir = vec3(0.5, 0.5, -1.0);

// Brightness control uniform
uniform float brightness = 1.0;

// Checkerboard function
float checkersGradBox(in vec2 p) {
    // Filter kernel
    vec2 w = fwidth(p) + 0.001;
    // Analytical integral (box filter)
    vec2 i = 2.0 * (abs(fract((p - 0.5 * w) * 0.5) - 0.5) - abs(fract((p + 0.5 * w) * 0.5) - 0.5)) / w;
    // XOR pattern
    return 0.5 - 0.5 * i.x * i.y;
}

// Raymarching for the floor
float raymarchFloor(in vec3 ro, in vec3 rd) {
    float t = (-ro.y) / rd.y; // Distance to the floor (y=0 plane)
    return t;
}

// Render function
vec4 render(in vec3 ro, in vec3 rd) {
    // Background color
    vec3 col = vec3(0.7, 0.7, 0.9) - max(rd.y, 0.0) * 0.3;

    // Raymarching to find intersection with the floor
    float t = raymarchFloor(ro, rd);

    if (t > 0.0) {
        // Calculate position on the floor
        vec3 pos = ro + t * rd;

        // Apply checkerboard pattern based on the position on the floor
        float check = checkersGradBox(3.0 * pos.xz);
        col = 0.15 + check * vec3(0.05);  // Checkerboard color

        // Lighting: using the user-defined light direction
        float diff = max(dot(vec3(0.0, 1.0, 0.0), normalize(lightDir)), 0.0);  // Diffuse lighting
        col *= diff;
    }

    // Apply brightness control
    col *= brightness;

    // Final color
    return vec4(col, 1.0);
}

vec3 CalcRayDir(vec2 nCoord) {
    vec3 horizontal = normalize(cross(camDir, vec3(0.0, 1.0, 0.0)));
    vec3 vertical = normalize(cross(horizontal, camDir));
    return normalize(camDir + horizontal * nCoord.x + vertical * nCoord.y);
}

mat3 setCamera() {
    vec3 cw = normalize(camDir);
    vec3 cp = vec3(0.0, 1.0, 0.0);
    vec3 cu = normalize(cross(cw, cp));
    vec3 cv = cross(cu, cw);
    return mat3(cu, cv, cw);
}

void main() {
    vec2 nCoord = (gl_FragCoord.xy - screenCenter.xy) / screenCenter.y;
    mat3 ca = setCamera();

    // Focal length
    float fl = length(camDir);
    vec3 rd = ca * normalize(vec3(nCoord, fl));

    // Render scene
    vec4 res = render(camPos, rd);
    gl_FragColor = res;
}
