#version 400 core

uniform mat4 mvp;

out vec4 in_color;

void main()
{
	const vec4 vertices[6] = vec4[6](	vec4( 1, -1, 0, 1.0),
										vec4(-1, -1, 0, 1.0),
										vec4( 1, 1, 0, 1.0),
										vec4( -1, -1, 0, 1.0),
										vec4(1, 1, 0, 1.0),
										vec4( -1, 1, 0, 1.0));
										
									
	const vec4 colors[6] = vec4[6](vec4(1, 1, 1, 1),
									vec4(0, 1, 0, 1), 
									vec4(0, 0, 1, 1),
									vec4(0, 1, 0, 1),
									vec4(0, 0, 1, 1), 
									vec4(1, 0, 0, 1));
									
									
	in_color = colors[gl_VertexID];
	gl_Position = mvp * vertices[gl_VertexID];
}