uniform vec4 offsetBeforeMVP;
uniform vec4 offsetAfterMVP;
void main()
{
    // transforme la position du vertex
    gl_Vertex += offsetBeforeMVP;
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex + offsetAfterMVP;

    // transforme les coordonnées de texture
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

    // transmet la couleur
    gl_FrontColor = gl_Color;
}
