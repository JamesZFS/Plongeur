#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Box2D/Common/b2Math.h>

extern const b2Vec2 c_gravity;  // gravity acceleration
extern const b2Vec2 c_world_top_left, c_world_bottom_right; // world boundaries in meters
extern const b2Vec2 c_world_center;
extern const float32 c_world_width, c_world_height;

extern const float32 c_actor_linear_damping;
extern const float32 c_actor_angular_damping;

extern const float32 c_diver_linear_damping;
extern const float32 c_diver_angular_damping;
extern const float32 c_diver_density;
extern const float32 c_diver_friction;
extern const float32 c_diver_restitution;

extern const float32 c_time_step;
extern const int32 c_velocity_iterations;
extern const int32 c_position_iterations;
extern const int32 c_particle_iterations;


#endif // CONSTANTS_H
