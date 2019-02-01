#version 130

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform float time;
uniform sampler2D mySampler;

void main()
{
	vec4 textureColor = texture(mySampler, fragmentUV) * fragmentColor;
	if (fragmentPosition.x < 0)
	{
		color = vec4(fragmentColor.r * cos(fragmentPosition.x + time),
					fragmentColor.g * cos(fragmentPosition.y + time),
					fragmentColor.b * cos(fragmentPosition.x + time),
					fragmentColor.a * cos(time)) * textureColor;
	}
	else
	{
		color = vec4(fragmentColor.r * sin(fragmentPosition.x * 2 + time) + 1.0 * 0.5,
					fragmentColor.g * sin(fragmentPosition.y * 8 + time) + 1.0 * 0.5,
					fragmentColor.b * sin(fragmentPosition.x * 3 + time) + 1.0 * 0.5,
					fragmentColor.a * sin(time)) * textureColor;
	}
//	color = vec4(fragmentColor.r * cos(fragmentPosition.x * 2 + time) + 1.0 * 0.5,
//					fragmentColor.g * cos(fragmentPosition.y * 8 + time) + 1.0 * 0.5,
//					fragmentColor.b * cos(fragmentPosition.x * 3 + time) + 1.0 * 0.5,
//					cos(fragmentColor.a)) * textureColor;
	
}