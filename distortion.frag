#version 330 core

uniform vec3 iResolution;
uniform float iTime;
uniform float iTimeDelta;
uniform int iFrame;
uniform float iChannelTime[4];
uniform vec3 iChannelResolution[4];
uniform vec4 iMouse;
uniform vec4 iDate;

float noise(vec2 p)
{
    float s = sin(p.x + p.y);
    s *= s;
    return s;
}

float onOff(float a, float b, float c)
{
    return step(c, sin(iTime + a * cos(iTime * b)));
}

float ramp(float y, float start, float end)
{
    float inside = step(start, y) - step(end, y);
    float fact = (y - start) / (end - start) * inside;
    return (1. - fact) * inside;
}

float stripes(vec2 uv)
{
    float noi = noise(uv * vec2(0.5, 1.) + vec2(1., 3.));
    return ramp(mod(uv.y * 4. + iTime / 2. + sin(iTime + sin(iTime * 0.63)), 1.), 0.5, 0.6) * noi;
}

vec2 screenDistort(vec2 uv)
{
    uv -= vec2(.5, .5);
    uv = uv * 1.2 * (1. / 1.2 + 2. * uv.x * uv.x * uv.y * uv.y);
    uv += vec2(.5, .5);
    return uv;
}

void main()
{
    vec2 uv = gl_FragCoord.xy / iResolution.xy;
    uv = screenDistort(uv);
    float vigAmt = 3. + .3 * sin(iTime + 5. * cos(iTime * 5.));
    float vignette = (1. - vigAmt * (uv.y - .5) * (uv.y - .5)) * (1. - vigAmt * (uv.x - .5) * (uv.x - .5));
    float stripesValue = stripes(uv);
    float noiseValue = noise(uv * 2.) / 2.;
    float finalValue = stripesValue + noiseValue;
    finalValue *= vignette;
    finalValue *= (12. + mod(uv.y * 30. + iTime, 1.)) / 13.;

    gl_FragColor = vec4(finalValue, finalValue, finalValue, 1.0);
}

