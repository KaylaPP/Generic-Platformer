#include "LoopingEntity.hpp"
#include <chrono>
#include <thread>

bool kpg::LoopingEntity::Spawn()
{
    std::thread calcthread(&LoopingEntity::CalcThread, this);
    calcthread.detach();
    return true;
}

void kpg::LoopingEntity::CalcThread()
{
    if(!OnCreate()) return;
    
    auto period = std::chrono::milliseconds(Period.getNumerator());
    auto next = std::chrono::steady_clock::now();
    auto prev = next - period;
    while (!end)
    {
        auto now = std::chrono::steady_clock::now();
        prev = now;
        
        if(!OnUpdate()) break;
        
        next += period;
        std::this_thread::sleep_until(next);
    }
    
    OnDestroy();
}
