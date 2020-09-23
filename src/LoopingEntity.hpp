#ifndef LoopingEntity_hpp
#define LoopingEntity_hpp

#include <string>

namespace kpg
{
    enum class EntityType
    {
        PLAYER,
        BALL
    };

    struct Collision
    {
        float XPos;
        float YPos;
        float XVel;
        float YVel;
        float mass;
    };

    class LoopingEntity
    {
    protected:
        bool end = false;
        float Mass;
        float XPos, YPos;
        float XVel, YVel;
        uint32_t Period; // In milliseconds
    private:
        virtual bool OnCreate();
        virtual bool OnUpdate();
        virtual bool OnDestroy();
        void CalcThread();
    public:
        bool Exists();
        bool Spawn();
        float GetXPos();
        float GetYPos();
        void Destroy();
    };

}

#endif /* LoopingEntity_hpp */
