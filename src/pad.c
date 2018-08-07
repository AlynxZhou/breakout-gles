#include "pad.h"

void pd_update(struct pad *pdp, float dt)
{
	pdp->position  = v2add(pdp->position, v2multiply(pdp->speed, dt));
}

void pd_render(struct pad *pdp, render *r)
{
	r_render(r, pdp->position, pdp->size, 0, pdp->color, pdp->texture);
}
