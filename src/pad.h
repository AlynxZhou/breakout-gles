#ifndef __PAD_H__
#	define __PAD_H__
#	include <GLES3/gl3.h>
#	include "mvmath/mvmath.h"
#	include "render.h"

struct pad {
	vec2 position;
	vec2 size;
	vec2 speed;
	vec4 color;
	GLuint texture;
};

void pd_update(struct pad *pdp, float dt);
void pd_render(struct pad *pdp, render *r);
#endif
