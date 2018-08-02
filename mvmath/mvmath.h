#ifndef __MVMATH_H__
#	define __MVMATH_H__
#	define PI 3.1415926
/*
 * mat is a scalar[16] like this:
 * |   0   4   8  12   |
 * |   1   5   9  13   |
 * |   2   6  10  14   |
 * |   3   7  11  15   |
 */
typedef float scalar;
typedef struct {
	scalar x;
	scalar y;
	scalar z;
} vec3;
typedef struct {
	scalar m[16];
} mat4;
vec3 vec3s(scalar x, scalar y, scalar z);
vec3 vnormalize(vec3 v1);
vec3 vadd(vec3 v1, vec3 v2);
vec3 vsubstract(vec3 v1, vec3 v2);
vec3 vcross(vec3 v1, vec3 v2);
scalar vdot(vec3 v1, vec3 v2);
vec3 vmultiply(vec3 v1, scalar s);
mat4 midentity(void);
mat4 mtranslate(vec3 delta);
mat4 mscale(vec3 scale);
mat4 mrotate(vec3 axis, scalar angle);
mat4 mperspective(scalar fov, scalar aspect, scalar near, scalar far);
mat4 mcamera(vec3 eye, vec3 target, vec3 up);
mat4 mmultiply(mat4 m1, mat4 m2);
#endif
