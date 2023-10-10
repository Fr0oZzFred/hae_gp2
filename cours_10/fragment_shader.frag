uniform float time;
uniform sampler2D texture;
uniform vec4 colorAdd;
uniform vec4 colorMul;
uniform mat4 matrix;
#define COLOR_ADD
#define COLOR_MUL
//#define COLOR_MAT


void main()
{

    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
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
