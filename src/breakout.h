#ifndef __BREAKOUT_H__
#	define __BREAKOUT_H__
#	include <stddef.h>
#	include <stdbool.h>
#	include <GLES3/gl3.h>
#	include "render.h"
#	include "ball.h"
#	include "brick.h"
#	include "pad.h"

#	define KEYS_LENGTH 1024
#	define BRICKS_LENGTH 36

enum br_status {MENU, READY, FIRED, DEAD, FINISHED};

typedef struct breakout {
	enum br_status status;
	bool keys[KEYS_LENGTH];
	GLuint width;
	GLuint height;
	render *render;
	vec2 initial_ball_speed;
	vec2 initial_pad_speed;
	struct ball ball;
	struct brick bricks[BRICKS_LENGTH];
	struct pad pad;
} breakout;

breakout *br_create(void);
void br_init(breakout *br, GLuint width, GLuint height);
void br_process_input(breakout *br, GLfloat delta_time);
void br_update(breakout *br, GLfloat delta_time);
void br_render(breakout *br);
void br_delete(breakout *br);
#endif
