#include <ecsviz/viz.h>
#include <ecsviz/Geometries.h>
#include <ecsviz/DrawInstances.h>
#include <ecsviz/DrawText.h>
#include <ecsviz/DrawPoints.h>
#include <ecsviz/DrawShapes.h>
#include <ecsviz/Cameras.h>
#include <ecsviz/Windows.h>
#include <ecsviz/Pointclouds.h>
#include <ecsviz/Sg.h>
#include <ecsviz/ecsviz_fs.h>



#include <stdio.h>
#include <assert.h>



int main(int argc, char *argv[])
{
	fs_pwd();

	ecs_world_t *world = ecs_init();

	// Must import before loading flecs file
	ECS_IMPORT(world, Sg);
	ECS_IMPORT(world, DrawInstances);
	ECS_IMPORT(world, DrawPoints);
	ECS_IMPORT(world, DrawShapes);
	ECS_IMPORT(world, DrawText);
	ECS_IMPORT(world, Geometries);
	ECS_IMPORT(world, Pointclouds);
	ECS_IMPORT(world, Cameras);
	ECS_IMPORT(world, Windows);

	// https://www.flecs.dev/explorer/?remote=true
	ecs_set(world, EcsWorld, EcsRest, {.port = 0});
	ecs_plecs_from_file(world, "render.flecs");
	ecs_plecs_from_file(world, "shapes.flecs");
	//ecs_plecs_from_file(world, "profile.flecs");
	// ecs_set_threads(world, 4);

	while (0)
	{
		ecs_progress(world, 0);
	}

	viz_state_t state = {.world = world};
	viz_init(&state);
	viz_run(&state);

	return ecs_fini(world);
}