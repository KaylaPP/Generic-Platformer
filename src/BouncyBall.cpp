#include "BouncyBall.hpp"
#include "EntityVars.hpp"

bool BouncyBall::OnCreate()
{
    Gravity = 1000.0f;
    XPos = float(rand() % (nWindowWidth - 32));
    YPos = float(rand() % (nWindowHeight - 32));
    YVel = float(rand() % 1000);
    XVel = float(rand() % 1000);
    Period = 1; // In milliseconds

    return true;
}

bool BouncyBall::OnUpdate()
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

bool BouncyBall::OnDestroy()
{
    return true;
}
