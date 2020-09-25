#include "BouncyBall.hpp"
#include "EntityVars.hpp"

kpg::BouncyBall::BouncyBall(float XPos, float YPos, float XVel, float YVel)
{
    this->XPos = XPos;
    this->YPos = YPos;
    this->XVel = XVel;
    this->YVel = YVel;
}

bool kpg::BouncyBall::OnCreate()
{
    Height = 32.0f;
    Width = 32.0f;
    Gravity = 1000.0f;
    Period = 10; // In milliseconds
    etype = EntityType::BALL;
    return true;
}

bool kpg::BouncyBall::OnUpdate()
{
    if(start)
    {
        YVel += Gravity * Period / 1000.0f;
        YPos += YVel * Period / 1000.0f;
        XPos += XVel * Period / 1000.0f;
        if(YPos < 0)
        {
            YPos = 0;
            YVel = YVel * -0.95f;
        }
        if(YPos > nWindowHeight - Height)
        {
            YPos = nWindowHeight - Height;
            YVel = YVel * -0.95f;
        }
        if(XPos < 0)
        {
            XPos = 0;
            XVel = XVel * -0.95f;
        }
        if(XPos > nWindowWidth - Width)
        {
            XPos = nWindowWidth - Width;
            XVel = XVel * -0.95f;
        }
        
        // Collision detection
        for(auto e : Entities)
        {
            kpg::LoopingEntity * E = e.second.second;
            if(E == this)
                break;
            switch(E->GetEntityType())
            {
            default:
                break;
            case kpg::EntityType::BALL:
                bool collides = 
                (
                    E->GetXPos() + E->GetWidth() > XPos &&
                    E->GetYPos() + E->GetHeight() > YPos &&
                    XPos + Width > E->GetXPos() &&
                    YPos + Height > E->GetYPos()
                );
                break;
            }
        }
        // Parse collision list
        CollisionMutex.lock();
        while(!Collisions.empty())
        {
            Collision col = Collisions.front();
            Collisions.pop();
        }
        CollisionMutex.unlock();
    }

    return true;
}

bool kpg::BouncyBall::OnDestroy()
{
    return true;
}
