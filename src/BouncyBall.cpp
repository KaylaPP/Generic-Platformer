#include "BouncyBall.hpp"
#include "EntityVars.hpp"
#include <iostream>

int signof(float f)
{
    if(f == 0.0f)
        return 0;
    else if(f > 0.0f)
        return 1;
    else
        return -1;
}

kpg::BouncyBall::BouncyBall(float XPos, float YPos, float XVel, float YVel)
{
    this->XPos = XPos;
    this->YPos = YPos;
    this->XVel = XVel;
    this->YVel = YVel;
}

bool kpg::BouncyBall::OnCreate()
{
    Diameter = 32.0f;
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
        if(YPos > nWindowHeight - Diameter)
        {
            YPos = nWindowHeight - Diameter;
            YVel = YVel * -0.95f;
        }
        if(XPos < 0)
        {
            XPos = 0;
            XVel = XVel * -0.95f;
        }
        if(XPos > nWindowWidth - Diameter)
        {
            XPos = nWindowWidth - Diameter;
            XVel = XVel * -0.95f;
        }
        
        // Collision detection
        for(auto e : Entities)
        {
            kpg::LoopingEntity * E = e.second.second;
            if(E != this)
            {
                switch(E->GetEntityType())
                {
                default:
                    break;
                case kpg::EntityType::PLAYER:
                    if(E->GetXPos() + nPlayerWidth >= XPos &&
                        E->GetXPos() <= XPos + Diameter &&
                        E->GetYPos() + nPlayerHeight >= YPos &&
                        E->GetYPos() <= YPos + Diameter)
                    {
                        Destroy();
                    }
                    break;
                case kpg::EntityType::BALL:
                    const float XCENTER = (XPos + Diameter / 2.0f);
                    const float YCENTER = (YPos + Diameter / 2.0f);
                    const float EXCENTER = (E->GetXPos() + Diameter / 2.0f);
                    const float EYCENTER = (E->GetYPos() + Diameter / 2.0f);

                    const float distance = std::sqrtf(std::powf(XCENTER - EXCENTER, 2.0f) + std::powf(YCENTER - EYCENTER, 2.0f));
                    if(distance < Diameter)
                    {
                        const float theta = std::atanf((YCENTER - EYCENTER) / (XCENTER - EXCENTER));
                        const int coefficient = 10;
                        if(!isnan(cosf(theta)))
                        {
                            XVel += coefficient * signof(XCENTER - EXCENTER) * cosf(theta);
                        }
                        if(!isnan(sinf(theta)))
                        {
                            YVel += coefficient * signof(YCENTER - EYCENTER) * sinf(theta);
                        }
                    }

                    break;
                }
            }
        }
    }

    return true;
}

bool kpg::BouncyBall::OnDestroy()
{
    return true;
}
