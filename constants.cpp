#include "constants.h"

// notice that the y-axis is heading down the screen
const b2Vec2 c_gravity = {0, 9.8f};
const b2Vec2 c_world_top_left{0, 0}, c_world_bottom_right{18, 25};

const b2Vec2 c_world_center((c_world_top_left + c_world_bottom_right) / 2);
const float32 c_world_width = c_world_bottom_right.x - c_world_top_left.x;
const float32 c_world_height = c_world_bottom_right.y - c_world_top_left.y;

const float32 c_actor_linear_damping = 0.1;
const float32 c_actor_angular_damping = 0.2;

const float32 c_diver_linear_damping = 0.1;
const float32 c_diver_angular_damping = 0.2;
const float32 c_diver_density = 1.2;
const float32 c_diver_friction = 0.6;
const float32 c_diver_restitution = 0.2;

const float32 c_time_step = 1.f / 60.f;
const int32 c_velocity_iterations = 5;
const int32 c_position_iterations = 2;
const int32 c_particle_iterations = 2;

const uint16 c_head_category = 1 << 1;
const uint16 c_limb_category = 1 << 2;

const float32 c_water_particle_radius = 0.08f;
const float32 c_water_density = 1.0f;
const float32 c_water_damping = 0.5f;

const double c_score_per_pose = 20;
const double c_score_per_round = 30;
const size_t c_measure_iters = 10;
