#define PI 3.1415926538
#define TAU 2.0*PI

precision highp float;
precision highp int;

varying vec2 UV;

uniform float dissolve;
uniform float globalAlpha;

uniform sampler2D baseTexture;
uniform sampler2D noiseTexture;
uniform sampler2D rampTexture;

float map(float value, float inMin, float inMax, float outMin, float outMax) {
    return outMin + (outMax - outMin) * (value - inMin) / (inMax - inMin);
}

vec2 map(vec2 value, vec2 inMin, vec2 inMax, vec2 outMin, vec2 outMax) {
    return outMin + (outMax - outMin) * (value - inMin) / (inMax - inMin);
}

vec3 map(vec3 value, vec3 inMin, vec3 inMax, vec3 outMin, vec3 outMax) {
    return outMin + (outMax - outMin) * (value - inMin) / (inMax - inMin);
}

vec4 map(vec4 value, vec4 inMin, vec4 inMax, vec4 outMin, vec4 outMax) {
    return outMin + (outMax - outMin) * (value - inMin) / (inMax - inMin);
}

void main() {
    vec2 uv_remapped = map(UV, vec2(0.0, 1.0), vec2(1.0, 0.0), vec2(-1.0, -1.0), vec2(1.0, 1.0));
    float mask = texture2D(noiseTexture, UV).r;
    float dissolve_remapped = map(dissolve, 0.0, 1.0, 1.0, 0.0);
    dissolve_remapped = map(dissolve_remapped, 0.0, 1.0, -0.5, 0.5);
    
    float mask_remapped = map(mask + dissolve_remapped, 0.0, 1.0, -4.0, 4.0);
    mask_remapped = 1.0 - clamp(mask_remapped, 0.0, 1.0);
    vec3 ramp_color = texture2D(rampTexture, vec2(mask_remapped, 0.0)).rgb;

    vec4 pixel = texture2D(baseTexture, UV);
    float alpha = mask + dissolve_remapped < 0.5 ? 0.0 : 1.0;

    gl_FragColor.rgb = pixel.rgb + ramp_color;
    gl_FragColor.a = pixel.a * alpha * globalAlpha;
}
