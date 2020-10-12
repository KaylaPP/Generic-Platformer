/*
 * MovingPlatforms are objects that move in one dimension and have "hard" collision
 * They do not react to physical interactions and will remain in their current position on their current path
 * no matter how hard it is hit by any object
 * They can be used as normal collision boxes or moving collision boxes
 * FlipPeriod is the period of time between flipping velocities or other behavior
 * MovingPlatform is meant to be the base class for other derivative classes
 * making it simpler to create other repeating and physics-defying objects
 */


#ifndef MovingPlatform_hpp
#define MovingPlatform_hpp

#include "LoopingEntity.hpp"

class MovingPlatform : public kpg::LoopingEntity
{
private:
    float FlipPeriod;
    
};

#endif