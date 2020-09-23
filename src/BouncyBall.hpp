#ifndef BouncyBall_hpp
#define BouncyBall_hpp

#include "LoopingEntity.hpp"

namespace kpg
{
    class BouncyBall : public kpg::LoopingEntity
    {
    public:
        BouncyBall(float XPos = 0.0f, float YPos = 0.0f, float XVel = 0.0f, float YVel = 0.0f);
    private:
        float Gravity;

        bool OnCreate() override;
        bool OnUpdate() override;
        bool OnDestroy() override;

    };
}

#endif /* BouncyBall_hpp */
