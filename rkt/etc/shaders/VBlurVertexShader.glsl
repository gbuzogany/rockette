precision highp float;
precision highp int;

attribute vec4 a_position;

varying vec2 v_texCoord;
varying vec2 v_blurTexCoords[14];

uniform highp mat4 projection;
uniform float blurAmount;

void main()
{
    gl_Position = projection * vec4(a_position.xy, 0.0, 1.0);
    v_texCoord = vec2(a_position.zw);
    v_blurTexCoords[ 0] = v_texCoord + vec2(0.0, -blurAmount*7.0);
    v_blurTexCoords[ 1] = v_texCoord + vec2(0.0, -blurAmount*6.0);
    v_blurTexCoords[ 2] = v_texCoord + vec2(0.0, -blurAmount*5.0);
    v_blurTexCoords[ 3] = v_texCoord + vec2(0.0, -blurAmount*4.0);
    v_blurTexCoords[ 4] = v_texCoord + vec2(0.0, -blurAmount*3.0);
    v_blurTexCoords[ 5] = v_texCoord + vec2(0.0, -blurAmount*2.0);
    v_blurTexCoords[ 6] = v_texCoord + vec2(0.0, -blurAmount);
    v_blurTexCoords[ 7] = v_texCoord + vec2(0.0,  blurAmount);
    v_blurTexCoords[ 8] = v_texCoord + vec2(0.0,  blurAmount*2.0);
    v_blurTexCoords[ 9] = v_texCoord + vec2(0.0,  blurAmount*3.0);
    v_blurTexCoords[10] = v_texCoord + vec2(0.0,  blurAmount*4.0);
    v_blurTexCoords[11] = v_texCoord + vec2(0.0,  blurAmount*5.0);
    v_blurTexCoords[12] = v_texCoord + vec2(0.0,  blurAmount*6.0);
    v_blurTexCoords[13] = v_texCoord + vec2(0.0,  blurAmount*7.0);
}
