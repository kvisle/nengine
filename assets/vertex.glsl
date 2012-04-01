uniform mat4 u_projectionMatrix;
attribute vec4 a_position;

attribute vec2 aTextureCoord;
varying vec2 vTextureCoord;

void main()
{
   gl_Position = u_projectionMatrix * a_position;
   vTextureCoord = aTextureCoord;
}

