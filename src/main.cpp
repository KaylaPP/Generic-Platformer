#define OLC_PGE_APPLICATION
#include "Fraction.hpp"
#include "LoopingEntity.hpp"
#include "olcPixelGameEngine.h"

#include <cstdlib>

const int nWindowWidth = 1280;
const int nWindowHeight = 800;

bool start = false;
bool bJumped = false;
bool bMovingLeft = false;
bool bMovingRight = false;

bool isPositive(Fraction f)
{
    return double(f.getNumerator()) / double(f.getDenominator()) > 0;
}

Fraction abs(Fraction f)
{
    Fraction absfrac(f);
    f.setNumerator(std::abs(f.getNumerator()));
    f.setDenominator(std::abs(f.getDenominator()));
    return f;
}

class BouncyBall : public kpg::LoopingEntity
{
private:
    Fraction Gravity;
    Fraction XPos, YPos;
    Fraction XVel, YVel;
public:
    BouncyBall()
    {
        img = "ball.png";
    }
    
private:
    std::string img;
    
    void OnCreate() override
    {
        Gravity = Fraction(1000);
        XPos = Fraction(rand() % (nWindowWidth - 32));
        YPos = Fraction(rand() % (nWindowHeight - 32));
        YVel = Fraction(0);
        XVel = Fraction(500);
        Period = Fraction(10); // In milliseconds
        
        Period.setDenominator(1000); // For easy conversion to seconds in multiplication
    }
    
    void OnUpdate() override
    {
        if(start)
        {
            YVel += Gravity * Period;
            YPos += YVel * Period;
            XPos += XVel * Period;
            if(YPos < Fraction(0))
            {
                YPos = Fraction(0);
                YVel = YVel * Fraction(-1);
            }
            if(YPos > Fraction(nWindowHeight - 32))
            {
                YPos = Fraction(nWindowHeight - 32);
                YVel = YVel * Fraction(-1);
            }
            if(XPos < Fraction(0))
            {
                XPos = Fraction(0);
                XVel = XVel * Fraction(-1);
            }
            if(XPos > Fraction(nWindowWidth - 32))
            {
                XPos = Fraction(nWindowWidth - 32);
                XVel = XVel * Fraction(-1);
            }
            
            XPos.reduce();
            YPos.reduce();
            YVel.reduce();
            XVel.reduce();
        }
    }
    
    void OnDestroy() override
    {
        
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
    Fraction Gravity;
    Fraction XPos, YPos;
    Fraction XVel, YVel;
    Fraction XAccel;
    Fraction XVelMax;
public:
    Player()
    {
        // Select image file here
        img = "player.png";
    }
private:
    std::string img;
    
    void OnCreate() override
    {
        // Override values here. Do some other stuff too maybe
        // Velocity is pixels per second and acceleration is pixels per second^2
        Gravity = Fraction(1000);
        XPos = Fraction(0);
        YPos = Fraction(0);
        YVel = Fraction(0);
        XVel = Fraction(200);
        XAccel = Fraction(1000);
        XVelMax = Fraction(500);
        Period = Fraction(10); // In milliseconds
        
        Period.setDenominator(1000); // For easy conversion to seconds in multiplication
    }
    
    void OnUpdate() override
    {
        if(start)
        {
            if(bMovingLeft)
                XVel -= XAccel * Period;
            if(bMovingRight)
                XVel += XAccel * Period;
            
            if(!bMovingLeft && !bMovingRight)
            {
                if(isPositive(XVel))
                {
                    XVel -= XAccel * Period;
                    if(XVel < Fraction(0))
                    {
                        XVel = Fraction(0);
                    }
                }
                else
                {
                    XVel += XAccel * Period;
                    if(XVel > Fraction(0))
                    {
                        XVel = Fraction(0);
                    }
                }
            }
            
            if(abs(XVel) > abs(XVelMax))
            {
                XVel = isPositive(XVel) ? XVelMax : XVelMax * Fraction(-1);
            }
            
            if(bJumped)
            {
                YVel = Fraction(-1000);
                bJumped = false;
            }
            
            YVel += Gravity * Period;
            YPos += YVel * Period;
            XPos += XVel * Period;
            if(YPos < Fraction(0))
            {
                YPos = Fraction(0);
                YVel = Fraction(0);
            }
            if(YPos > Fraction(nWindowHeight - 64))
            {
                YPos = Fraction(nWindowHeight - 64);
                YVel = Fraction(0);
            }
            if(XPos < Fraction(0))
            {
                XPos = Fraction(0);
                XVel = Fraction(0);
            }
            if(XPos > Fraction(nWindowWidth - 64))
            {
                XPos = Fraction(nWindowWidth - 64);
                XVel = Fraction(0);
            }
            
            XPos.reduce();
            YPos.reduce();
            YVel.reduce();
            XVel.reduce();
        }
    }
    
    void OnDestroy() override
    {
        
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
    Player p;
    olc::Renderable player;
    BouncyBall bs[5];
    olc::Renderable balls[5];
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
        
        for(int i = 0; i < 5; i++)
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
        
        
        for(int i = 0; i < 5; i++)
        {
            if(bs[i].Exists())
            {
                DrawDecal({ bs[i].GetXPos(), bs[i].GetYPos() }, balls[i].Decal());
            }
        }
        
        
        DrawStringDecal({ 0.0f, 0.0f }, std::to_string(p.GetXPos()) + ", " + std::to_string(p.GetYPos()) + ", " + std::to_string(p.GetXVel()) + ", " + std::to_string(p.GetYVel()), {0, 255, 0});
        return true;
    }
};

int main(int argc, char const *argv[])
{
    srand(time(nullptr));
	PortalDemo demo;
	if (demo.Construct(nWindowWidth, nWindowHeight, 1, 1, false, true))
		demo.Start();

	return 0;
}
