varying vec2 vTextureCoord;
uniform sampler2D mytex;

void main()
{
    gl_FragColor = texture2D (mytex, vec2 (vTextureCoord.s, vTextureCoord.t)).rgba;
}
