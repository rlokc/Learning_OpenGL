#version 330 core

in vec2 TexCoord;

out vec4 fragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixer;

void main()
{
    //fragColor = vec4(ourColor, 1.0f);
    //fragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
    vec4 texel0, texel1;
    texel0 = texture(texture1, TexCoord);
    texel0 = texel0 * mixer;
    texel1 = texture(texture2, TexCoord);
    fragColor = mix(texel1, texel0, texel0.a);
}
