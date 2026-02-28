#version 450 core

#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

// Inputs 
// Uniforms - Push Constants
layout (push_constant) uniform Params
{
	vec2 u_resolution; // screen canvas resolution in physical pixels
};

// Input Attributes
layout (location = 0) in vec3 pos;      // "vanilla" vertex position attribute - given in pixels
layout (location = 1) in uint word;     // per-instance: four chars
layout (location = 2) in vec3 word_pos; // per-instance: where to place the word in screen space
layout (location = 3) in vec4 col_fg;   // per-instance: foreground colour
layout (location = 4) in vec4 col_bg;   // per-instance: background colour

// Vertex Outputs 
struct per_word_data {
	uint msg;
	vec4 fg_colour;
	vec4 bg_colour;
};

out gl_PerVertex { vec4 gl_Position; };
layout (location = 0) out vec2 outTexCoord;
layout (location = 1) flat out per_word_data outMsg;

void main() 
{
	outMsg.msg = word;
	outMsg.fg_colour = col_fg;
	outMsg.bg_colour = col_bg;

	vec2 scale_factor = vec2(1.,2.)/(u_resolution);
	outTexCoord = vec2((12 >> gl_VertexIndex) &1, (9 >> gl_VertexIndex ) &1);
	vec4 position = vec4(0,0,0,1);
	position.xy = vec2(-1, -1) + (pos.xy * word_pos.z + word_pos.xy) * scale_factor;
	gl_Position = position;
}