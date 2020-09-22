#define OLC_PGE_APPLICATION
#include "LoopingEntity.hpp"
#include "olcPixelGameEngine.h"

#include <cstdlib>
#include <unordered_map>

const int nWindowWidth = 640;
const int nWindowHeight = 480;

bool start = false;
bool bJumped = false;
bool bMovingLeft = false;
bool bMovingRight = false;

class BouncyBall : public kpg::LoopingEntity
{
private:
    float Gravity;
    float XPos, YPos;
    float XVel, YVel;
public:
    BouncyBall()
    {
        img = "ball.png";
    }
    
private:
    std::string img;
    
    bool OnCreate() override
    {
        Gravity = 1000.0f;
        XPos = float(rand() % (nWindowWidth - 32));
        YPos = float(rand() % (nWindowHeight - 32));
        YVel = float(rand() % 1000);
        XVel = float(rand() % 1000);
        Period = 20; // In milliseconds

        return true;
    }
    
    bool OnUpdate() override
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
    
    bool OnDestroy() override
    {
        return true;
    }
    
public:
    bool Exists()
    {
        return !end;
    }
    
    float GetXPos()
    {
        return float(XPos);
    }
    
    float GetYPos()
    {
        return float(YPos);
    }
    
    float GetXVel()
    {
        return float(XVel);
    }
    
    float GetYVel()
    {
        return float(YVel);
    }
    
    void Destroy()
    {
        end = true;
    }
    
    std::string GetImageName()
    {
        return img;
    }
};

class Player : public kpg::LoopingEntity
{
private:
    float Gravity;
    float XPos, YPos;
    float XVel, YVel;
    float XAccel;
    float XVelMax;
public:
    Player()
    {
        // Select image file here
        img = "player.png";
    }
private:
    std::string img;
    
    bool OnCreate() override
    {
        // Override values here. Do some other stuff too maybe
        // Velocity is pixels per second and acceleration is pixels per second^2
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
    
    bool OnUpdate() override
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
            if(YPos > nWindowHeight - 64)
            {
                YPos = float(nWindowHeight - 64);
                YVel = 0.0f;
            }
            if(XPos < 0)
            {
                XPos = 0.0f;
                XVel = 0.0f;
            }
            if(XPos > nWindowWidth - 64)
            {
                XPos = float(nWindowWidth - 64);
                XVel = 0.0f;
            }
        }

        return true;
    }
    
    bool OnDestroy() override
    {
        return true;
    }
    
public:
    bool Exists()
    {
        return !end;
    }
    
    float GetXPos()
    {
        return float(XPos);
    }
    
    float GetYPos()
    {
        return float(YPos);
    }
    
    float GetXVel()
    {
        return float(XVel);
    }
    
    float GetYVel()
    {
        return float(YVel);
    }
    
    void Destroy()
    {
        end = true;
    }
    
    std::string GetImageName()
    {
        return img;
    }
};

class PortalDemo : public olc::PixelGameEngine
{
private:
#define ballcount 1
    Player p;
    olc::Renderable player;
    BouncyBall bs[ballcount];
    olc::Renderable balls[ballcount];
public:
    PortalDemo()
    {
        sAppName = "Gravity";
    }

public:
    bool OnUserCreate() override
    {
        p.Spawn();
        player.Load(p.GetImageName());
        
        for(int i = 0; i < ballcount; i++)
        {
            bs[i].Spawn();
            balls[i].Load(bs[i].GetImageName());
        }
        
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        Clear(olc::BLACK);

        if(GetKey(olc::E).bPressed)
            return false;

        if(p.Exists())
            DrawDecal({ p.GetXPos(), p.GetYPos() }, player.Decal());
        if(GetKey(olc::SPACE).bPressed)
            start = true;
        
        if(GetKey(olc::LEFT).bHeld)
            bMovingLeft = true;
        else
            bMovingLeft = false;
        if(GetKey(olc::RIGHT).bHeld)
            bMovingRight = true;
        else
            bMovingRight = false;
        if(GetKey(olc::UP).bPressed)
            bJumped = true;
        
        
        for(int i = 0; i < ballcount; i++)
        {
            if(bs[i].Exists())
            {
                DrawDecal({ bs[i].GetXPos(), bs[i].GetYPos() }, balls[i].Decal());
            }
        }
        
        
        DrawStringDecal({ 0.0f, 0.0f }, std::to_string(p.GetXPos()) + ", " + std::to_string(p.GetYPos()) + ", " + std::to_string(p.GetXVel()) + ", " + std::to_string(p.GetYVel()), {0, 255, 0});
        return true;
    }

    bool OnUserDestroy() override 
    {
        p.Destroy();

        for(int i = 0; i < ballcount; i++)
        {
            bs[i].Destroy();
        }

        return true;
    }
};

int main(int argc, char const *argv[])
{
    srand(uint32_t(time(nullptr)));
	PortalDemo demo;
	if (demo.Construct(nWindowWidth, nWindowHeight, 1, 1, false, true))
		demo.Start();

	return 0;
}
