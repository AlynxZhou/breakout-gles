#include <stdlib.h>
#include <string.h>
#include "render.h"

render *r_create(void)
{
	render *r = malloc(sizeof(*r));
	r->program = 0;
	r->quad_vao = 0;
	r->texture = 0;
	return r;
}

void r_init(render *r, GLuint program)
{
	r->program = program;
	GLuint vbo;
	GLfloat vertices[] = {
		// 位置     // 纹理
        	0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
        	0.0f, 0.0f, 0.0f, 0.0f,

        	0.0f, 1.0f, 0.0f, 1.0f,
        	1.0f, 1.0f, 1.0f, 1.0f,
        	1.0f, 0.0f, 1.0f, 0.0f
	};
	glUseProgram(r->program);
	glGenVertexArrays(1, &(r->quad_vao));
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
		     vertices, GL_STATIC_DRAW);
	glBindVertexArray(r->quad_vao);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
			      4 * sizeof(GLfloat), NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void r_render(render *r, vec2 position, vec2 size, \
	      GLfloat rotate, vec4 color, GLuint texture)
{
	glUseProgram(r->program);
	mat4 model = m4translate(v3v2s(position, 0.0f));
	model = m4multiply(model, m4translate(v3v2s(v2multiply(size, \
							       0.5f), 0.0f)));
	model = m4multiply(model, m4rotate(v3s(0.0f, 0.0f, 1.0f), rotate));
	model = m4multiply(model, m4translate(v3v2s(v2multiply(size, \
							       -0.5f), 0.0f)));
	model = m4multiply(model, m4scale(v3v2s(size, 1.0f)));
	glUniformMatrix4fv(glGetUniformLocation(r->program, "model"), \
			   1, GL_FALSE, model.m);
	glUniform4f(glGetUniformLocation(r->program, "color"), \
		    color.v[0], color.v[1], color.v[2], color.v[3]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(r->quad_vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glUseProgram(0);
}

void r_delete(render *r)
{
	free(r);
}
