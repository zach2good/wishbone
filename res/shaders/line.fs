#version 150 core

out vec4 outColor;

#define resolution vec2(800.0, 600.0)
#define Thickness 0.003

float drawLine(vec2 p1, vec2 p2) {
  vec2 uv = gl_FragCoord.xy / resolution.xy;

  float a = abs(distance(p1, uv));
  float b = abs(distance(p2, uv));
  float c = abs(distance(p1, p2));

  if ( a >= c || b >=  c ) return 0.0;

  float p = (a + b + c) * 0.5;

  // median to (p1, p2) vector
  float h = 2 / c * sqrt( p * ( p - a) * ( p - b) * ( p - c));

  return mix(1.0, 0.0, smoothstep(0.5 * Thickness, 1.5 * Thickness, h));
}

void main()
{
  outColor = vec4(
      max(
        max(
          drawLine(vec2(0.1, 0.1), vec2(0.1, 0.9)),
          drawLine(vec2(0.1, 0.9), vec2(0.7, 0.5))),
        drawLine(vec2(0.1, 0.1), vec2(0.7, 0.5))));
}