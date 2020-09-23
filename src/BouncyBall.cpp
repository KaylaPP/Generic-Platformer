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
    Gravity = 1000.0f;
    Period = 10; // In milliseconds

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
        if(YPos > nWindowHeight - 32)
        {
            YPos = nWindowHeight - 32;
            YVel = YVel * -0.95f;
        }
        if(XPos < 0)
        {
            XPos = 0;
            XVel = XVel * -0.95f;
        }
        if(XPos > nWindowWidth - 32)
        {
            XPos = nWindowWidth - 32;
            XVel = XVel * -0.95f;
        }
    }

    return true;
}

bool kpg::BouncyBall::OnDestroy()
{
    return true;
}
