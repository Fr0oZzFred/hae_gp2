uniform float time;
uniform sampler2D texture;

uniform vec4 colorAdd;
uniform vec4 colorMul;
uniform mat4 matrix;

uniform float distortionPower;
uniform sampler2D noiseTexture;

uniform vec2 spherizeCenter;
uniform vec2 spherizeOffset;
uniform float spherizeStrength;

uniform vec2 blurOffsetFactor;

//varying vec2 pos; How to get a var from vertex shader

#define COLOR_ADD
#define COLOR_MUL
//#define COLOR_MAT

//#define TEX_DISTORTION
//#define WAVE_DISTORTION
#define SPHERIZE_DISTORTION

//#define COLOR_WITH_UV

//#define BLUR



void main()
{

    //Texture Distortion
#ifdef TEX_DISTORTION
    vec4 distortion = texture2D(noiseTexture, gl_TexCoord[0].xy)* distortionPower;
#endif

#ifdef WAVE_DISTORTION
    //Wave Distortion
    vec4 distortion = gl_TexCoord[0];
    distortion.x += sin(distortion.y*distortionPower+time)/distortionPower;
#endif

#ifdef SPHERIZE_DISTORTION
    float2 delta = gl_TexCoord[0].xy - spherizeCenter;
    float delta2 = dot(delta.xy, delta.xy);
    float delta4 = delta2 * delta2;
    float2 delta_offset = delta4 * spherizeStrength;
    vec4 distortion = vec4(delta * delta_offset + spherizeOffset,0.0,0.0);
#endif

#if defined(TEX_DISTORTION) || defined(WAVE_DISTORTION)|| defined(SPHERIZE_DISTORTION)
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy + distortion.xy);
#else
    //Frac Distortion
    vec2 uv = gl_TexCoord[0].xy;
    uv = fract(uv * distortionPower);
    vec2 smooth_uv = distortionPower * gl_TexCoord[0].xy;
    vec4 duv = vec4(dFdx(smooth_uv), dFdy(smooth_uv));
    vec4 pixel = textureGrad(texture, uv, duv.xy, duv.zw);
#endif



    gl_FragColor = pixel;

#ifdef COLOR_ADD
    gl_FragColor += (colorAdd * (cos(time) + 1.0) * 0.5);
#endif

#ifdef COLOR_MUL
    gl_FragColor *= (colorMul * (cos(time) + 1.0) * 0.5);
#endif

#ifdef COLOR_MAT
    gl_FragColor *= matrix;
#endif

#ifdef COLOR_WITH_UV
    gl_FragColor += gl_TexCoord[0];
#endif

#ifdef BLUR
vec2 uv = gl_TexCoord[0].xy;
vec4 color = vec4(0.0);
color += texture2D(texture, uv - 4.0 * blurOffsetFactor) * 0.0162162162;
color += texture2D(texture, uv - 3.0 * blurOffsetFactor) * 0.0540540541;
color += texture2D(texture, uv - 2.0 * blurOffsetFactor) * 0.1216216216;
color += texture2D(texture, uv - blurOffsetFactor) * 0.1945945946;
color += texture2D(texture, uv) * 0.2270270270;
color += texture2D(texture, uv + blurOffsetFactor) * 0.1945945946;
color += texture2D(texture, uv + 2.0 * blurOffsetFactor) * 0.1216216216;
color += texture2D(texture, uv + 3.0 * blurOffsetFactor) * 0.0540540541;
color += texture2D(texture, uv + 4.0 * blurOffsetFactor) * 0.0162162162;
gl_FragColor = color;

#endif
}
