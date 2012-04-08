varying vec2 vTextureCoord;
varying vec4 vColor;
uniform sampler2D mytex;
attribute vec4 aColor;
attribute float useTex;
varying float vUseTex;

void main()
{
/*    float r = texture2D (mytex, vec2 (vTextureCoord.s, vTextureCoord.t)).r * vColor[0];
    float g = texture2D (mytex, vec2 (vTextureCoord.s, vTextureCoord.t)).g * vColor[1];
    float b = texture2D (mytex, vec2 (vTextureCoord.s, vTextureCoord.t)).b * vColor[2];
    float a = texture2D (mytex, vec2 (vTextureCoord.s, vTextureCoord.t)).a * vColor[3];*/

    if ( vUseTex == 1.0f )
    {
        gl_FragColor = texture2D (mytex, vec2 (vTextureCoord.s, vTextureCoord.t)).rgba * vColor;
    }
    else
    {
        gl_FragColor = vColor;
    }
//    gl_FragColor = vec4(r, g, b, a);
//    gl_FragColor = texture2D (mytex, vec2 (vTextureCoord.s, vTextureCoord.t)).rgba * vColor;
}
