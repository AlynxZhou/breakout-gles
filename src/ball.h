#ifndef __BALL_H__
#	define __BALL_H__
#	include <stddef.h>
#	include <stdbool.h>
#	include <GLES3/gl3.h>
#	include "mvmath/mvmath.h"
#	include "render.h"
#	include "brick.h"
#	include "pad.h"

struct ball {
	vec2 position;
	vec2 size;
	vec2 speed;
	vec4 color;
	GLuint texture;
};

enum direction {UP, RIGHT, DOWN, LEFT, NONE};
struct collision {
	enum direction dir;
	vec2 diff;
};

struct collision bl_collision_brick(struct ball *blp, struct brick *bkp);
bool bl_collision_pad(struct ball *blp, struct pad *pdp);
void bl_update(struct ball *blp, float dt);
void bl_render(struct ball *blp, render *r);
#endif
