#include "ball.h"
#include <stdio.h>

struct collision bl_collision_brick(struct ball *blp, struct brick *bkp)
{
	float radius = blp->size.v[0] / 2.0f;
	vec2 bl_center = v2s(blp->position.v[0] + radius, \
			  blp->position.v[1] + radius);
	vec2 bk_half_size = v2multiply(bkp->size, 0.5f);
	vec2 bk_center = v2add(bkp->position, bk_half_size);
	vec2 center_difference = v2substract(bl_center, bk_center);
	vec2 clamped = v2clamp(center_difference, \
			       v2multiply(bk_half_size, -1.0f), \
			       bk_half_size);
	vec2 bk_closet = v2add(bk_center, clamped);
	vec2 difference = v2substract(bk_closet, bl_center);
	if (v2length(difference) > radius)
		return (struct collision){NONE, v2s(0, 0)};
	const vec2 compass[] = {
		// UP
		v2s(0.0f, 1.0f),
		// RIGHT
		v2s(1.0f, 0.0f),
		// DOWN
		v2s(0.0f, -1.0f),
		// LEFT
		v2s(-1.0f, 0.0f)
	};
	float max = 0.0f;
	size_t best_match = 4;
	for (size_t i = 0; i < 4; ++i) {
		float dot = v2dot(v2normalize(difference), compass[i]);
		if (dot > max) {
			max = dot;
			best_match = i;
		}
	}
	return (struct collision){best_match, \
				  v2substract(v2s(radius, radius), \
				  	      v2abs(difference))};
}

bool bl_collision_pad(struct ball *blp, struct pad *pdp)
{
	float radius = blp->size.v[0] / 2;
	vec2 bl_center = v2s(blp->position.v[0] + radius, \
			  blp->position.v[1] + radius);
	vec2 bk_half_size = v2multiply(pdp->size, 0.5f);
	vec2 bk_center = v2add(pdp->position, bk_half_size);
	vec2 center_difference = v2substract(bl_center, bk_center);
	vec2 clamped = v2clamp(center_difference, \
			       v2multiply(bk_half_size, -1.0f), \
			       bk_half_size);
	vec2 bk_closet = v2add(bk_center, clamped);
	vec2 difference = v2substract(bk_closet, bl_center);
	return v2length(difference) < radius;
}

void bl_update(struct ball *blp, float dt)
{
	blp->position  = v2add(blp->position, v2multiply(blp->speed, dt));
}

void bl_render(struct ball *blp, render *r)
{
	r_render(r, blp->position, blp->size, 0, blp->color, blp->texture);
}
