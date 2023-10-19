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
uniform float davidBlurFactor;

//varying vec2 pos; How to get a var from vertex shader

#define COLOR_ADD
#define COLOR_MUL
//#define COLOR_MAT

//#define TEX_DISTORTION
//#define WAVE_DISTORTION
#define SPHERIZE_DISTORTION

//#define COLOR_WITH_UV

//#define BLUR
//#define DAVID_3X3

//#define NOISE

//#define PATTERN_CHECKER
 #define DISSOLVE

#ifdef DAVID_3X3
float luma(vec4 col) {
  return col.a *(col.r * .3 + col.g * 0.59 + col.b * 0.11);
}
#endif

#ifdef NOISE
float random (vec2 uv) {
    return fract(sin(dot(uv.xy,
                         vec2(12.9898,78.233)))*
        43758.5453123);
}
#endif

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

#ifdef DAVID_3X3
    pixel += texture2D(texture, gl_TexCoord[0] + vec2((davidBlurFactor / 475), 0.0));
    pixel += texture2D(texture, gl_TexCoord[0] - vec2((davidBlurFactor / 475), 0.0));

    pixel*= 0.33;


    pixel += texture2D(texture, gl_TexCoord[0] + vec2((davidBlurFactor / 475), 0.0)) * 0.125f;
    pixel += texture2D(texture, gl_TexCoord[0] - vec2((davidBlurFactor / 475), 0.0)) * 0.125f;
    pixel += texture2D(texture, gl_TexCoord[0] + vec2(0.0, (davidBlurFactor / 475))) * 0.125f;
    pixel += texture2D(texture, gl_TexCoord[0] - vec2(0.0, (davidBlurFactor / 475))) * 0.125f;
#endif

#ifdef NOISE
    pixel = random(gl_TexCoord[0]);
#endif

#ifdef PATTERN_CHECKER
    float x = step(fract(gl_TexCoord[0].x * distortionPower), 0.5f);
    float y = step(fract(gl_TexCoord[0].y * distortionPower), 0.5f);
    float resR = x * y;
    float resB = 1.0f-(x+y);
    float res = max(resR, resB);
    pixel = vec4(res);
#endif

#ifdef DISSOLVE
    pixel.a -= texture2D(noiseTexture, gl_TexCoord[0].xy).r * distortionPower;
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
