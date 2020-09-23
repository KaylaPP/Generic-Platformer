#include "LoopingEntity.hpp"
#include <chrono>
#include <thread>

class EntityLoopException : public std::exception
{
public:
    EntityLoopException(std::string exception)
    {
        err = exception;
    }
    
private:
    std::string err;
    const char * what () const throw ()
    {
        return err.c_str();
    }
    
};

bool kpg::LoopingEntity::Exists()
{
    return !end;
}

bool kpg::LoopingEntity::Spawn()
{
    std::thread calcthread(&LoopingEntity::CalcThread, this);
    calcthread.detach();
    return true;
}

bool kpg::LoopingEntity::OnCreate()
{
    return true;
}
bool kpg::LoopingEntity::OnUpdate()
{
    return true;
}
bool kpg::LoopingEntity::OnDestroy()
{
    return true;
}

float kpg::LoopingEntity::GetYPos()
{
    return YPos;
}

float kpg::LoopingEntity::GetXPos()
{
    return XPos;
}

void kpg::LoopingEntity::CalcThread()
{
    if(!OnCreate()) throw EntityLoopException("OnCreate method error");
    
    auto period = std::chrono::milliseconds(Period);
    auto next = std::chrono::steady_clock::now();
    auto prev = next - period;
    while (!end)
    {
        auto now = std::chrono::steady_clock::now();
        prev = now;
        
        if(!OnUpdate()) throw EntityLoopException("OnUpdate method error");
        
        next += period;
        std::this_thread::sleep_until(next);
    }
    
    if(!OnDestroy()) throw EntityLoopException("OnDestroy method error");
}

void kpg::LoopingEntity::Destroy()
{
    end = true;
}
