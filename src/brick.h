#ifndef __BRICK_H__
#	define __BRICK_H__
#	include <GLES3/gl3.h>
#	include "mvmath/mvmath.h"
#	include "render.h"

struct brick {
	vec2 position;
	vec2 size;
	vec4 color;
	GLuint texture;
	unsigned int life;
};

void bk_render(struct brick *bkp, render *r);
#endif
