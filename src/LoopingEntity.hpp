#ifndef LoopingEntity_hpp
#define LoopingEntity_hpp

#include <string>

namespace kpg
{
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
        float XPos, YPos;
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
