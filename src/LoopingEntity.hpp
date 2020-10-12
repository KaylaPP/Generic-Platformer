/*
 * LoopingEntities in general have soft collision boundaries
 * Meaning if you want precise collision detection for something like
 * A moving platform, you'd want th
 */


#ifndef LoopingEntity_hpp
#define LoopingEntity_hpp

#include <mutex>
#include <string>
#include <queue>

namespace kpg
{
    enum class EntityType
    {
        STATIC,
        PLAYER,
        BALL
    };

    class LoopingEntity
    {
    protected:
        bool end = false;
        float XPos, YPos;
        float XVel, YVel;
        uint32_t Period; // In milliseconds
        EntityType etype;
    private: // Multithreading
        virtual bool OnCreate();
        virtual bool OnUpdate();
        virtual bool OnDestroy();
        void CalcThread();
    public: // Get Entity Characteristics
        bool Exists();
        bool Spawn();
        EntityType GetEntityType();
        float GetXPos();
        float GetYPos();
        float GetXVel();
        float GetYVel();
        void Destroy();
    };

}

#endif /* LoopingEntity_hpp */
