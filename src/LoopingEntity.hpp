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
        uint32_t ID;
    private:
        virtual bool OnCreate() = 0;
        virtual bool OnUpdate() = 0;
        virtual bool OnDestroy() = 0;
        void CalcThread();
    public:
        bool Exists();
        bool Spawn();
        float GetXPos();
        float GetYPos();
        uint32_t getID();
        void Destroy();
    };

}

#endif /* LoopingEntity_hpp */
