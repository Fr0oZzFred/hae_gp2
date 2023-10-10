uniform float time;
uniform float distortionPower;
uniform sampler2D texture;
uniform sampler2D noiseTexture;
uniform vec4 colorAdd;
uniform vec4 colorMul;
uniform mat4 matrix;


#define COLOR_ADD
#define COLOR_MUL
//#define COLOR_MAT


void main()
{

    //Texture Distortion
    //vec4 distortion = texture2D(noiseTexture, gl_TexCoord[0].xy)* distortionPower;

    //Wave Distortion
    //vec4 distortion = gl_TexCoord[0];
    //distortion.x += sin(distortion.y*distortionPower+time)/distortionPower;

    //vec4 pixel = texture2D(texture, gl_TexCoord[0].xy + distortion.xy);


    //Frac Distortion
    vec2 uv = gl_TexCoord[0].xy;
    uv = fract(uv * distortionPower);
    vec2 smooth_uv = distortionPower * gl_TexCoord[0].xy;
    vec4 duv = vec4(dFdx(smooth_uv), dFdy(smooth_uv));
    vec4 pixel = textureGrad(texture, uv, duv.xy, duv.zw);


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
}
