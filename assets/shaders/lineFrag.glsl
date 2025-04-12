#version 420

varying vec3 fColor;
varying vec2 fTex;

uniform sampler2D tex;
uniform sampler2D tex2;

void main() 
{
	float firstLine = smoothstep(0,0.005,abs(fTex.y - 0.33f));
	float secondLine = smoothstep(0,0.005,abs(fTex.y - 0.66f));
	vec3 color = vec3(0.0f);

	float smoothStepLinearVal = abs(fTex.y - mix(0.33f,0.66f, fTex.x));
	float linearLine = smoothstep(0,0.0075,smoothStepLinearVal);

	float smoothStepSmoothVal = abs(fTex.y - mix(0.66f,1.00f, smoothstep(0.0, 1.0,fTex.x)));
	float smoothLine = smoothstep(0, 0.0075, smoothStepSmoothVal);

	float smoothStepStepVal = abs(fTex.y - mix(0.0f,0.33f, step(0.5, fTex.x)));
	float stepLine = smoothstep(0, 0.0075, smoothStepStepVal);

	vec3 red = vec3(1.0,0.0,0.0);
	vec3 blue = vec3(0.0,0.0,1.0);
	vec3 white = vec3(1.0,1.0,1.0);

	if(fTex.y < 0.33f)
	{
		color = mix(red, blue, step(0.5, fTex.x));
	}
	else if(fTex.y < 0.66)
	{
		color = mix(white, blue, fTex.x);
	}
	else
	{
		color =  mix(red, white, smoothstep(0.0, 1.0,fTex.x));
	}

	color = mix(white, color, firstLine);
	color = mix(white, color, secondLine);
	color = mix(white, color, linearLine);
	color = mix(white, color, smoothLine);
	color = mix(white, color, stepLine);

	gl_FragColor = vec4(color,1.0);

}