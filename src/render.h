#ifndef __RENDER_H__
#	define __RENDER_H__

#	include <GLES3/gl3.h>
#	include "mvmath/mvmath.h"

typedef struct render {
	GLuint program;
	GLuint quad_vao;
	GLuint texture;
} render;

render *r_create(void);
void r_init(render *r, GLuint program);
void r_render(render *r, vec2 position, vec2 size, \
	      GLfloat rotate, vec4 color, GLuint texture);
void r_delete(render *r);
#endif
