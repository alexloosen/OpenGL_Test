#version 130

in vec4 fragmentColor;
in vec2 fragmentPosition;
in vec2 fragmentUV;

out vec4 color;

uniform float time;
uniform sampler2D mySampler;

vec2 sineWave(vec2 p)
{
	//p.x=( 0.55*p.x)+0.5;
	//p.y=(-0.55*p.y)+0.5;
    // wave distortion
    float x = sin( 25.0*p.y + 15.0*p.x + 10 * time) * 0.015;
    float y = sin( 25.0*p.y + 15.0*p.x + 10 * time) * 0.015;
    return vec2(p.x + x, p.y + y);
}

void main()
{
	vec4 textureColor;
	vec2 flip = vec2(fragmentUV.x, -fragmentUV.y);;
	if(fragmentPosition.y >= 50)
	{
		textureColor = texture(mySampler, fragmentUV) * fragmentColor;
		color = vec4(fragmentColor.r + cos(time) * 0.02,
					fragmentColor.g + cos(time) * 0.02,
					fragmentColor.b + cos(time) * 0.02,
					fragmentColor.a) * textureColor;
	}
	else
	{
		textureColor = texture(mySampler, sineWave(flip)) * fragmentColor;
			color = vec4(fragmentColor.r + cos(time) * 0.02,
					fragmentColor.g + cos(time) * 0.02,
					fragmentColor.b + cos(time) * 0.02 + 1,
					fragmentColor.a) * textureColor;
	}
	
	if (fragmentPosition.x > 50 && fragmentPosition.x < 100)
	{
		textureColor = texture(mySampler, fragmentUV) * fragmentColor;
		color = vec4(fragmentColor.r * cos(0.05*fragmentPosition.x+2*time) + 0.5 * 0.2,
					fragmentColor.g * cos(0.05*fragmentPosition.x+2*time) + 0.5 * 0.2,
					fragmentColor.b * cos(0.05*fragmentPosition.x+2*time) + 0.5 * 0.2,
					fragmentColor.a) * textureColor;
	}
	if (fragmentPosition.x > 100 && fragmentPosition.x < 150)
	{
		textureColor = texture(mySampler, fragmentUV) * fragmentColor;
			color = vec4(fragmentColor.r * cos(0.05*fragmentPosition.y+2*time) + 0.5 * 0.2,
						fragmentColor.g * cos(0.05*fragmentPosition.y+2*time) + 0.5 * 0.2,
						fragmentColor.b * cos(0.05*fragmentPosition.y+2*time) + 0.5 * 0.2,
						fragmentColor.a) * textureColor;
	}
	if (fragmentPosition.x > 150)
	{
		float dis = distance(fragmentPosition, vec2(175,75));
		textureColor = texture(mySampler, fragmentUV) * fragmentColor;
		vec4 yellow = vec4(1.000,0.60,0.25,sin(1.0-(dis/20.0))*0.25*time);
		float pct = abs(sin(time));
		color = mix(vec4(0,0,0,0),yellow,pct*2) * textureColor;
	}
}