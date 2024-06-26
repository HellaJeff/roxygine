#include <linmath.h>
#include "../global.h"
#include "../util.h"
#include "physics.h"
#include "physics_internal.h"

static physics_state_internal_t phys_state;

void physics_init(void) {
	phys_state.body_list = array_list_new(sizeof(body_t), 0);
}

void physics_update(void) {
	
	body_t *body_cursor;
	
	for(size_t c = 0; c < phys_state.body_list->length; c++) {
		
		body_cursor = (body_t *)array_list_get(phys_state.body_list, c);
		
		//fprintf(stdout, "Body index: %zu\n\tBody pos: (%f, %f)\n\tBody vel: (%f, %f)\n", c, body_cursor->aabb.position[0], body_cursor->aabb.position[1], body_cursor->velocity[0], body_cursor->velocity[1]);
		
		body_cursor->velocity[0] += body_cursor->acceleration[0] * global.time.delta;
		body_cursor->velocity[1] += body_cursor->acceleration[1] * global.time.delta;
		body_cursor->aabb.position[0] += body_cursor->velocity[0] * global.time.delta;
		body_cursor->aabb.position[1] += body_cursor->velocity[1] * global.time.delta;
		
		//fprintf(stdout, "Body index: %zu\n\tBody pos: (%f, %f)\n\tBody vel: (%f, %f)\n", c, body_cursor->aabb.position[0], body_cursor->aabb.position[1], body_cursor->velocity[0], body_cursor->velocity[1]);
		
	}
	
}

size_t physics_body_create(vec2 position, vec2 size) {
	
	body_t new_body = {
		.aabb = {
			.position = {position[0], position[1]},
			.half_size = {size[0] * 0.5, size[1] * 0.5}
		},
		.velocity = {0, 0}
	};
	
	if(array_list_push(phys_state.body_list, &new_body) == (size_t)(-1))
		ERROR_EXIT(-1, "Could not append new body to physics list\n");
	
	return phys_state.body_list->length - 1;
	
}

body_t *physics_body_get(size_t index) {
	return array_list_get(phys_state.body_list, index);
}