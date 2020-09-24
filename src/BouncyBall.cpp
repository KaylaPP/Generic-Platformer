#include "BouncyBall.hpp"
#include "EntityVars.hpp"

kpg::BouncyBall::BouncyBall(float XPos, float YPos, float XVel, float YVel)
{
    Height = 32.0f;
    Width = 32.0f;
    Mass = 10.0f;
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
            ProcessingCollision = true;
            switch(E->GetEntityType())
            {
            case kpg::EntityType::PLAYER:
                if(XVel > 0) // Right
                {
                    if(YVel > 0) // Falling
                    {
                        if(GetSE().X >= E->GetNW().X && GetSE().Y >= E->GetNW().Y)
                        {
                            E->Collide({ XVel, YVel, Mass });
                            Collide({ E->GetXVel(), E->GetYVel(), E->GetMass() });
                        }
                    }
                    else if(YVel < 0) // Up
                    {
                        if(GetNE().X >= E->GetSW().X && GetNE().Y <= E->GetSW().Y)
                        {
                            E->Collide({ XVel, YVel, Mass });
                            Collide({ E->GetXVel(), E->GetYVel(), E->GetMass() });
                        }
                    }
                }
                else if(XVel < 0) // Left
                {
                    if(YVel > 0) // Falling
                    {
                        if(GetSW().X <= E->GetNE().X && GetSW().Y >= E->GetNE().Y)
                        {
                            E->Collide({ XVel, YVel, Mass });
                            Collide({ E->GetXVel(), E->GetYVel(), E->GetMass() });
                        }
                    }
                    else if(YVel < 0) // Up
                    {
                        if(GetNW().X <= E->GetSE().X && GetNW().Y <= E->GetSE().Y)
                        {
                            E->Collide({ XVel, YVel, Mass });
                            Collide({ E->GetXVel(), E->GetYVel(), E->GetMass() });
                        }
                    }
                }
                break;
            case kpg::EntityType::BALL:
                if(XVel > 0) // Right
                {
                    if(YVel > 0) // Falling
                    {
                        
                    }
                    else if(YVel < 0) // Up
                    {
                        
                    }
                }
                else if(XVel < 0) // Left
                {
                    if(YVel > 0) // Falling
                    {
                        
                    }
                    else if(YVel < 0) // Up
                    {
                        
                    }
                }
                break;
            }
            ProcessingCollision = false;
            // Parse collision list
            
            
        }
    }

    return true;
}

bool kpg::BouncyBall::OnDestroy()
{
    return true;
}
