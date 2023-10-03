uniform float time;
uniform sampler2D texture;
//#define COLOR_ADD
//#define COLOR_MUL
#define COLOR_MAT


void main()
{
    gl_TexCoord[0].xy + vec2(time,0.5);

    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    gl_FragColor = pixel;

    #ifdef COLOR_ADD
    gl_FragColor = pixel + vec4(
          (cos(time) + 1.0) * 0.5,
          0.0, 0.0, 1.0);
    #endif

    #ifdef COLOR_MUL
    gl_FragColor = pixel * vec4(
          (cos(time) + 1.0) * 0.5,
          0.0, 0.0, 1.0);
    #endif

    #ifdef COLOR_MAT
    gl_FragColor = pixel * mat4(0.3588, 0.7044, 0.1368, 0.0,
                                0.2990, 0.5870, 0.1140, 0.0,
                                0.2392, 0.4696, 0.0912 ,0.0,
                                0,0,0,1.0);
    #endif
}
