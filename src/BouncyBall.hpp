#ifndef BouncyBall_hpp
#define BouncyBall_hpp

#include "LoopingEntity.hpp"

class BouncyBall : public kpg::LoopingEntity
{
private:
    float Gravity;
    float XVel, YVel;

    bool OnCreate() override;
    bool OnUpdate() override;
    bool OnDestroy() override;
    
};

#endif /* BouncyBall_hpp */
