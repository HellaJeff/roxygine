#include <stdio.h>
#include <stdint.h>
#include <glad/glad.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "engine/global.h"
#include "engine/util.h"
#include "engine/render/render.h"
#include "engine/render/render_internal.h"


int32_t main(int32_t argc, char **argv) {
	
	render_init();
	
	char running = 1;
	
	while(running) {
		
		SDL_Event event;
		
		while(SDL_PollEvent(&event)) {
			
			switch(event.type) {
				
				case SDL_QUIT:
					running = 0;
					break;
					
				default:
					break;
				
			}
			
		}
		
		render_begin();
	
		render_quad(
					(vec2){global.render.width * 0.5, global.render.height * 0.5},
					(vec2){50, 50},
					(vec4){1, 0, 1, 1}
					);
					
		render_end();
		
	}
	
	return 0;
	
}