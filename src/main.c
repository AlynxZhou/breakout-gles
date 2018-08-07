#include <stdio.h>
#include <GLFW/glfw3.h>
#include <GLES3/gl3.h>

#include "breakout.h"

void key_callback(GLFWwindow *window, int key, \
		  int scancode, int action, int mode);

const GLuint WINDOW_WIDTH = 1920;
const GLuint WINDOW_HEIGHT = 1080;

breakout *br = NULL;

int main(int argc, char *argv[])
{
	br = br_create();
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// glfwWindowHint(GLFW_OPENGL_ES_API, )
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "breakout", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);

	br_init(br, WINDOW_WIDTH, WINDOW_HEIGHT);

	GLfloat last_time = 0.0f;

	while (!glfwWindowShouldClose(window)) {
		GLfloat current_time = glfwGetTime();
		GLfloat delta_time = current_time - last_time;
		last_time = current_time;
		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		br_process_input(br, delta_time);
		br_update(br, delta_time);
		br_render(br);

		// printf("FPS: %8.3f\n", 1 / delta_time);
		glfwSwapBuffers(window);
	}

	br_delete(br);

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow *window, int key, \
		  int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < KEYS_LENGTH) {
		switch (action) {
		case GLFW_PRESS:
			br->keys[key] = true;
			break;
		case GLFW_RELEASE:
			br->keys[key] = false;
			break;
		default:
			break;
		}
	}
}
