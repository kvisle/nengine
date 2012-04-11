precision mediump float;
varying vec2 vTextureCoord;
varying vec4 vColor;
uniform sampler2D mytex;
varying float vUseTex;

void main()
{
    if ( vUseTex == 1.0 )
    {
        gl_FragColor = texture2D (mytex, vec2 (vTextureCoord.s, vTextureCoord.t)).rgba * vColor;
    }
    else
    {
        gl_FragColor = vColor;
    }
}
