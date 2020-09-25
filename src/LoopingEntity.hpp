#ifndef LoopingEntity_hpp
#define LoopingEntity_hpp

#include <mutex>
#include <string>
#include <queue>

namespace kpg
{
    enum class EntityType
    {
        PLAYER,
        BALL
    };

    struct Collision
    {
        EntityType E;
        float XVel;
        float YVel;
    };

    struct Coordinates
    {
        float X;
        float Y;
    };

    class LoopingEntity
    {
    public:
        std::mutex CollisionMutex;
    protected:
        bool end = false;
        bool ProcessingCollision = false;
        float Height, Width;
        float XPos, YPos;
        float XVel, YVel;
        uint32_t Period; // In milliseconds
        EntityType etype;
        std::queue<Collision> Collisions;
    private: // Multithreading
        virtual bool OnCreate();
        virtual bool OnUpdate();
        virtual bool OnDestroy();
        void CalcThread();
    public: // Get Entity Characteristics
        bool Exists();
        bool Spawn();
        EntityType GetEntityType();
        float GetHeight();
        float GetWidth();
        float GetMass();
        float GetXPos();
        float GetYPos();
        float GetXVel();
        float GetYVel();
        void Destroy();
    public: // Collision-related Methods
        void Collide(Collision c);
        Coordinates GetNE();
        Coordinates GetSE();
        Coordinates GetSW();
        Coordinates GetNW();
    };

}

#endif /* LoopingEntity_hpp */
