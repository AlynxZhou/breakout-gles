#include <stdlib.h>
#include <string.h>
#include <GLFW/glfw3.h>
#include "breakout.h"
#include "mvmath/mvmath.h"
#include "loaders/png_loader.h"
#include "loaders/program_loader.h"

breakout *br_create(void)
{
	breakout *br = malloc(sizeof(*br));
	br->width = 0;
	br->height = 0;
	for (size_t i = 0; i < KEYS_LENGTH; ++i)
		br->keys[i] = false;
	br->status = READY;
	br->render = NULL;
	return br;
}

void br_init(breakout *br, GLuint width, GLuint height)
{
	br->width = width;
	br->height = height;
	const GLuint program = load_program("../shaders/render.v.glsl", \
					    "../shaders/render.f.glsl");
	const mat4 projection = m4ortho(0.0f, br->width, br->height, \
					0.0f, -1.0f, 1.0f);
	glUseProgram(program);
	glUniform1i(glGetUniformLocation(program, "image"), 0);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection"), \
			   1, GL_FALSE, projection.m);
	glUseProgram(0);
	const GLuint brick_texture = load_png_texture("../textures/brick.png");
	const GLuint brick_solid_texture = load_png_texture("../textures/brick_solid.png");
	br->ball.texture = load_png_texture("../textures/huaji.png");
	br->ball.color = v4s(1.0f, 1.0f, 1.0f, 1.0f);
	br->ball.position = v2s(width / 2.0f - height / 20.0f,
				height - height / 20.0f - \
				height / 30.0f);
	br->ball.size = v2s(height / 20.0f, height / 20.0f);
	br->ball.speed = v2s(0.0f, 0.0f);
	br->initial_ball_speed = v2s(width / 3.0f, height / 3.0f);
	br->pad.texture = load_png_texture("../textures/pad.png");
	br->pad.color = v4s(1.0f, 1.0f, 1.0f, 1.0f);
	br->pad.position = v2s(width / 2.0f - width / 5.0f / 2.0f, \
			       height - height / 20.0f);
	br->pad.size = v2s(width / 5.0f, height / 20.0f);
	br->pad.speed = v2s(0.0f, 0.0f);
	br->initial_pad_speed = v2s(width / 2.0f, 0.0f);
	const size_t blockHeight = height / 10;
        const size_t blockWidth = width / 10;
	size_t count = 0;
	for (int i = 1; i < height / blockHeight - 5; i += 2) {
                for (int j = 0; j < width / blockWidth; ++j) {
			if (count > BRICKS_LENGTH)
				continue;
			br->bricks[count].position = v2s(j * blockWidth, i * blockHeight);
			br->bricks[count].size = v2s(blockWidth, blockHeight);
			br->bricks[count].color = v4s(0.5f, 0.8f, 1.0f, 1.0f);
			br->bricks[count].life = 1;
			br->bricks[count].texture = brick_texture;
			++count;
		}
	}
	br->render = r_create();
	r_init(br->render, program);
}

void br_process_input(breakout *br, GLfloat delta_time)
{
	if (br->keys[GLFW_KEY_A])
		br->pad.speed = v2multiply(br->initial_pad_speed, -1.0f);
	else if (br->keys[GLFW_KEY_D])
		br->pad.speed = br->initial_pad_speed;
	else
		br->pad.speed = v2s(0.0f, 0.0f);
	if (br->keys[GLFW_KEY_SPACE]) {
		if (br->status == READY || br->status == DEAD) {
			br->status = FIRED;
			br->ball.speed = v2s(0.0f, -br->initial_ball_speed.v[1]);
		} else if (br->status == FINISHED) {
			br->status = READY;
		}
	}
}

void br_update(breakout *br, GLfloat delta_time)
{
	pd_update(&(br->pad), delta_time);
	if (br->pad.position.v[0] < 0 - br->pad.size.v[0] / 2) {
		br->pad.position.v[0] = 0 - br->pad.size.v[0] / 2;
	}
	if (br->pad.position.v[0] > br->width - br->pad.size.v[0] / 2) {
		br->pad.position.v[0] = br->width - br->pad.size.v[0] / 2;
	}
	if (br->status == READY || br->status == DEAD)
		br->ball.position  = v2s(br->pad.position.v[0] + \
					 br->pad.size.v[0] / 2.0f - \
					 br->ball.size.v[0] / 2, \
					 br->pad.position.v[1] - \
					 br->ball.size.v[1]);
	bl_update(&(br->ball), delta_time);
	if (br->ball.position.v[0] < 0) {
		br->ball.position.v[0] = 0;
		br->ball.speed.v[0] = -br->ball.speed.v[0];
	}
	if (br->ball.position.v[0] > br->width - br->ball.size.v[0]) {
		br->ball.position.v[0] = br->width - br->ball.size.v[0];
		br->ball.speed.v[0] = -br->ball.speed.v[0];
	}
	if (br->ball.position.v[1] < 0) {
		br->ball.position.v[1] = 0;
		br->ball.speed.v[1] = -br->ball.speed.v[1];
	}
	if (bl_collision_pad(&(br->ball), &(br->pad)) && br->status == FIRED) {
		const float percentage = ((br->ball.position.v[0] + \
					   br->ball.size.v[0] / 2) - \
					  (br->pad.position.v[0] + \
					   br->pad.size.v[0] / 2)) / \
					 (br->pad.size.v[0] / 2);
		const int strength = 2;
		const vec2 new_speed = v2s(br->initial_ball_speed.v[0] * \
					   percentage * strength, \
					   -br->initial_ball_speed.v[0]);
		const float old_length = v2length(br->ball.speed);
		const float new_length = v2length(new_speed);
		br->ball.speed = v2multiply(new_speed, \
					    old_length / new_length);
	}
	if (br->ball.position.v[1] > br->width - br->ball.size.v[1] / 2) {
		br->status = DEAD;
		br->ball.position = v2s(br->width / 2.0f,
					br->height - br->height / 50.0f \
					- br->height / 70.0f);
		br->ball.speed = v2s(0.0f, 0.0f);
		br->pad.position = v2s(br->width / 2.0f - \
				       br->width / 3.0f / 2.0f, \
				       br->height - br->height / 50.0f);
		br->pad.speed = v2s(0.0f, 0.0f);
	}
	size_t bricks_alive = 0;
	for (size_t i = 0; i < BRICKS_LENGTH; ++i) {
		if (br->bricks[i].life <= 0)
			continue;
		struct collision c = bl_collision_brick(&(br->ball), \
							&(br->bricks[i]));
		switch (c.dir) {
		case UP:
			br->ball.speed.v[1] = -br->ball.speed.v[1];
			br->ball.position = v2add(br->ball.position, v2s(0.0f, c.diff.v[1]));
			break;
		case RIGHT:
			br->ball.speed.v[0] = -br->ball.speed.v[0];
			br->ball.position = v2add(br->ball.position, v2s(c.diff.v[0], 0.0f));
			break;
		case DOWN:
			br->ball.speed.v[1] = -br->ball.speed.v[1];
			br->ball.position = v2add(br->ball.position, v2s(0.0f, c.diff.v[1]));
			break;
		case LEFT:
			br->ball.speed.v[0] = -br->ball.speed.v[0];
			br->ball.position = v2add(br->ball.position, v2s(c.diff.v[0], 0.0f));
			break;
		case NONE:
		default:
			break;
		}
		if (c.dir == NONE)
			++bricks_alive;
		else
			--br->bricks[i].life;
	}
	if (!bricks_alive)
		br->status = FINISHED;
}

void br_render(breakout *br)
{
	for (size_t i = 0; i < BRICKS_LENGTH; ++i) {
		if (br->bricks[i].life <= 0)
			continue;
		bk_render(&(br->bricks[i]), br->render);
	}
	pd_render(&(br->pad), br->render);
	bl_render(&(br->ball), br->render);
}

void br_delete(breakout *br)
{
	free_program(br->render->program);
	free_png_texture(br->render->texture);
	glDeleteVertexArrays(1, &(br->render->quad_vao));
	r_delete(br->render);
	free(br);
}
