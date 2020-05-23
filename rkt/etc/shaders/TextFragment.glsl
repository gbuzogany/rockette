precision highp float;
precision highp int;

varying highp vec2 UV;

uniform sampler2D tex;
uniform highp vec3 textColor;

uniform float globalAlpha;

void main()
{
    highp vec4 sampled = vec4(1.0, 1.0, 1.0, texture2D(tex, UV).a);
    gl_FragColor = vec4(textColor, globalAlpha) * sampled;
}
