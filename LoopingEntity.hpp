#ifndef LoopingEntity_hpp
#define LoopingEntity_hpp

#include "Fraction.hpp"

namespace kpg
{
    class LoopingEntity
    {
    protected:
        bool end = false;
        Fraction nPeriod; // In milliseconds
    private:
        virtual void OnCreate() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnDestroy() = 0;
        void CalcThread();
    public:
        bool Spawn();
    };
};

#endif /* LoopingEntity_hpp */
