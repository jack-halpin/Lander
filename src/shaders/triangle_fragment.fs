#version 330 core

uniform vec3 uColour;
uniform vec4 uExpected;
uniform bool uFull;

out vec4 FragColor;
void main()
{
    vec4 frag = gl_FragCoord;

    if (uFull)
    {
        if (uExpected.x <= frag.x && frag.x <= uExpected.z && uExpected.y >= frag.y && frag.y >= uExpected.w)
            FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
        else
            discard;
    }
    
    else
        FragColor = vec4(uColour, 1.0f);
}