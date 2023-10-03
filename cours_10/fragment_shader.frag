uniform float time;
uniform sampler2D texture;
uniform vec4 color;
uniform mat4 matrix;
//#define COLOR_ADD
//#define COLOR_MUL
#define COLOR_MAT


void main()
{
    gl_TexCoord[0].xy + vec2(time,0.5);

    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    gl_FragColor = pixel;

#ifdef COLOR_ADD
    gl_FragColor = pixel + (color * (cos(time) + 1.0) * 0.5);
#endif

#ifdef COLOR_MUL
    gl_FragColor = pixel * (color * (cos(time) + 1.0) * 0.5);
#endif

#ifdef COLOR_MAT
    gl_FragColor = pixel * matrix;
#endif
}
