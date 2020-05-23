precision highp float;
precision highp int;

varying highp vec2 UV;

uniform sampler2D textureSampler;

uniform float globalAlpha;

void main(){
    gl_FragColor = texture2D( textureSampler, UV );
    gl_FragColor.a = gl_FragColor.a * globalAlpha;
}
