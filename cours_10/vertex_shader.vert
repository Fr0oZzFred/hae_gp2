uniform vec4 offsetBeforeMVP;
uniform vec4 offsetAfterMVP;

//varying vec2 pos; How to pass a var from vertex shader

void main()
{
    // transforme la position du vertex
    gl_Vertex += offsetBeforeMVP;
    //pos = gl_Vertex.xy;

    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex + offsetAfterMVP;

    // transforme les coordonnées de texture
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

    // transmet la couleur
    gl_FrontColor = gl_Color;
}
