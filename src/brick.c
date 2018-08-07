#include "brick.h"

void bk_render(struct brick *bkp, render *r)
{
	r_render(r, bkp->position, bkp->size, 0.0f, bkp->color, bkp->texture);
}
