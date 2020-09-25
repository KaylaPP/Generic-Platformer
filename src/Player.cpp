//
//  Player.cpp
//  Hello PGE
//
//  Created by Kevin Puig on 9/23/20.
//  Copyright © 2020 Kevin Puig. All rights reserved.
//

#include "Player.hpp"
#include "EntityVars.hpp"

bool kpg::Player::OnCreate()
{
    // Override values here. Do some other stuff too maybe
    // Velocity is pixels per second and acceleration is pixels per second^2
    Height = 64.0f;
    Width = 64.0f;
    Gravity = 1000.0f;
    XPos = 0.0f;
    YPos = 0.0f;
    YVel = 0.0f;
    XVel = 200.0f;
    XAccel = 1000.0f;
    XVelMax = 500.0f;
    Period = 1; // In milliseconds

    return true;
}

bool kpg::Player::OnUpdate()
{
    if(start)
    {
        if(bMovingLeft)
            XVel -= XAccel * Period / 1000.0f;
        if(bMovingRight)
            XVel += XAccel * Period / 1000.0f;
        
        if(!bMovingLeft && !bMovingRight)
        {
            if(XVel > 0)
            {
                XVel -= XAccel * Period / 1000.0f;
                if(XVel < 0)
                {
                    XVel = 0.0f;
                }
            }
            else
            {
                XVel += XAccel * Period / 1000.0f;
                if(XVel > 0)
                {
                    XVel = 0.0f;
                }
            }
        }
        
        if(abs(XVel) > abs(XVelMax))
        {
            XVel = XVel > 0 ? XVelMax : XVelMax * -1.0f;
        }
        
        if(bJumped)
        {
            YVel = -1000.0f;
            bJumped = false;
        }
        
        YVel += Gravity * Period / 1000.0f;
        YPos += YVel * Period / 1000.0f;
        XPos += XVel * Period / 1000.0f;
        if(YPos < 0)
        {
            YPos = 0.0f;
            YVel = 0.0f;
        }
        if(YPos > nWindowHeight - Height)
        {
            YPos = float(nWindowHeight - Height);
            YVel = 0.0f;
        }
        if(XPos < 0)
        {
            XPos = 0.0f;
            XVel = 0.0f;
        }
        if(XPos > nWindowWidth - Width)
        {
            XPos = float(nWindowWidth - Width);
            XVel = 0.0f;
        }
    }

    return true;
}

bool kpg::Player::OnDestroy()
{
    return true;
}
