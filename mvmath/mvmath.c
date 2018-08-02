#include <math.h>
#include "mvmath.h"

vec3 vec3s(scalar x, scalar y, scalar z)
{
	vec3 v;
	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}

vec3 vnormalize(vec3 v1)
{
	scalar d = sqrtf(vdot(v1, v1));
	return vmultiply(v1, 1.0f / d);
}

vec3 vadd(vec3 v1, vec3 v2)
{
	vec3 v;
	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return v;
}

vec3 vsubstract(vec3 v1, vec3 v2)
{
	vec3 v;
	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return v;
}

vec3 vcross(vec3 v1, vec3 v2)
{
	vec3 v;
	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return v;
}

scalar vdot(vec3 v1, vec3 v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vec3 vmultiply(vec3 v1, scalar s)
{
	vec3 v;
	v.x = v1.x * s;
	v.y = v1.y * s;
	v.z = v1.z * s;
	return v;
}

mat4 midentity(void)
{
	mat4 m;
        m.m[0] = 1.0f;
        m.m[1] = 0.0f;
        m.m[2] = 0.0f;
        m.m[3] = 0.0f;
        m.m[4] = 0.0f;
        m.m[5] = 1.0f;
        m.m[6] = 0.0f;
        m.m[7] = 0.0f;
        m.m[8] = 0.0f;
        m.m[9] = 0.0f;
        m.m[10] = 1.0f;
        m.m[11] = 0.0f;
        m.m[12] = 0.0f;
        m.m[13] = 0.0f;
        m.m[14] = 0.0f;
        m.m[15] = 1.0f;
	return m;
}

mat4 mtranslate(vec3 delta)
{
	mat4 m;
	m.m[0] = 1.0f;
	m.m[1] = 0.0f;
	m.m[2] = 0.0f;
	m.m[3] = 0.0f;
	m.m[4] = 0.0f;
	m.m[5] = 1.0f;
	m.m[6] = 0.0f;
	m.m[7] = 0.0f;
	m.m[8] = 0.0f;
	m.m[9] = 0.0f;
	m.m[10] = 1.0f;
	m.m[11] = 0.0f;
	m.m[12] = delta.x;
	m.m[13] = delta.y;
	m.m[14] = delta.z;
	m.m[15] = 1.0f;
	return m;
}

mat4 mscale(vec3 scale)
{
	mat4 m;
	m.m[0] = scale.x;
	m.m[1] = 0.0f;
	m.m[2] = 0.0f;
	m.m[3] = 0.0f;
	m.m[4] = 0.0f;
	m.m[5] = scale.y;
	m.m[6] = 0.0f;
	m.m[7] = 0.0f;
	m.m[8] = 0.0f;
	m.m[9] = 0.0f;
	m.m[10] = scale.z;
	m.m[11] = 0.0f;
	m.m[12] = 0.0f;
	m.m[13] = 0.0f;
	m.m[14] = 0.0f;
	m.m[15] = 1.0f;
	return m;
}

mat4 mrotate(vec3 axis, scalar angle)
{
	mat4 m;
	axis = vnormalize(axis);
	scalar s = sinf(angle);
	scalar c = cosf(angle);
	scalar temp = 1.0f - c;
	m.m[0] = temp * axis.x * axis.x + c;
	m.m[1] = temp * axis.x * axis.y - axis.z * s;
	m.m[2] = temp * axis.z * axis.x + axis.y * s;
	m.m[3] = 0.0f;
	m.m[4] = temp * axis.x * axis.y + axis.z * s;
	m.m[5] = temp * axis.y * axis.y + c;
	m.m[6] = temp * axis.y * axis.z - axis.x * s;
	m.m[7] = 0.0f;
	m.m[8] = temp * axis.z * axis.x - axis.y * s;
	m.m[9] = temp * axis.y * axis.z + axis.x * s;
	m.m[10] = temp * axis.z * axis.z + c;
	m.m[11] = 0.0f;
	m.m[12] = 0.0f;
	m.m[13] = 0.0f;
	m.m[14] = 0.0f;
	m.m[15] = 1.0f;
	return m;
}

mat4 mperspective(scalar fov, scalar aspect, scalar near, scalar far)
{
	mat4 m;
	scalar dz = near - far;
	scalar cot = 1.0f / tanf(fov / 2.0f);
	m.m[0] = cot / aspect;
        m.m[1] = 0.0f;
        m.m[2] = 0.0f;
        m.m[3] = 0.0f;
        m.m[4] = 0.0f;
        m.m[5] = cot;
        m.m[6] = 0.0f;
        m.m[7] = 0.0f;
        m.m[8] = 0.0f;
        m.m[9] = 0.0f;
        m.m[10] = (far + near) / dz;
        m.m[11] = -1.0f;
        m.m[12] = 0.0f;
        m.m[13] = 0.0f;
        m.m[14] = (2.0f * far * near) / dz;
        m.m[15] = 0.0f;
	return m;
}

mat4 mcamera(vec3 eye, vec3 target, vec3 up)
{
	mat4 m;
	vec3 direction = vsubstract(target, eye);
	direction = vnormalize(direction);
	vec3 right = vcross(direction, up);
	right = vnormalize(right);
	up = vcross(right, direction);
	m.m[0] = right.x;
	m.m[1] = up.x;
	m.m[2] = -direction.x;
	m.m[3] = 0.0f;
	m.m[4] = right.y;
	m.m[5] = up.y;
	m.m[6] = -direction.y;
	m.m[7] = 0.0f;
	m.m[8] = right.z;
	m.m[9] = up.z;
	m.m[10] = -direction.z;
	m.m[11] = 0.0f;
	m.m[12] = -vdot(right, eye);
	m.m[13] = -vdot(up, eye);
	m.m[14] = vdot(direction, eye);
	m.m[15] = 1.0f;
	return m;
}

mat4 mmultiply(mat4 m1, mat4 m2)
{
	mat4 m;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j) {
			m.m[i * 4 + j] = 0.0f;
			for (int k = 0; k < 4; ++k)
				m.m[i * 4 + j] += m1.m[k * 4 + j] * m2.m[i * 4 + k];
		}
	return m;
}
