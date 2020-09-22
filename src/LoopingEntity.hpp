#ifndef LoopingEntity_hpp
#define LoopingEntity_hpp

#include "Fraction.hpp"

namespace kpg
{
    class LoopingEntity
    {
    protected:
        bool end = false;
        Fraction Period; // In milliseconds
    private:
        virtual bool OnCreate() = 0;
        virtual bool OnUpdate() = 0;
        virtual bool OnDestroy() = 0;
        void CalcThread();
    public:
        bool Spawn();
    };
}

#endif /* LoopingEntity_hpp */
