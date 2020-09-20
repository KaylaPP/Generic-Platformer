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

Fraction abs(Fraction f)
{
    Fraction absfrac(f);
    f.setNumerator(std::abs(f.getNumerator()));
    f.setDenominator(std::abs(f.getDenominator()));
    return f;
}

class Player : public kpg::LoopingEntity
{
private:
    Fraction fGravity;
    Fraction fXPos, fYPos;
    Fraction fXVel, fYVel;
    Fraction fXAccel;
    Fraction fMaxXVel;
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
        fGravity = Fraction(1000);
        fXPos = Fraction(0);
        fYPos = Fraction(0);
        fYVel = Fraction(0);
        fXVel = Fraction(200);
        fXAccel = Fraction(1000);
        fMaxXVel = Fraction(500);
        nPeriod = Fraction(10); // In milliseconds
        
        nPeriod.setDenominator(1000); // For easy conversion to seconds in multiplication
    }
    
    void OnUpdate() override
    {
        if(start)
        {
            if(bMovingLeft)
                fXVel -= fXAccel * nPeriod;
            else if(!bMovingLeft && !bMovingRight)
                fXVel += fXAccel * nPeriod;
            if(bMovingRight)
                fXVel += fXAccel * nPeriod;
            else if(!bMovingLeft && !bMovingRight)
                fXVel -= fXAccel * nPeriod;
            
            if(abs(fXVel) > abs(fMaxXVel))
            {
                
            }
            //if(fXVel < Fraction(-1) * fMaxXVel)
            //    fXVel = Fraction(-1) * fMaxXVel;
            //if(fXVel < 0.1f + float(nPeriod) && fXVel > -0.1f - float(nPeriod) && !bMovingLeft && !bMovingRight)
            //    fXVel = 0.0f;
            if(bJumped)
            {
                fYVel = Fraction(-1000);
                bJumped = false;
            }
            
            fYVel += fGravity * nPeriod;
            fYPos += fYVel * nPeriod;
            fXPos += fXVel * nPeriod;
            if(fYPos < Fraction(0))
            {
                fYPos = Fraction(0);
                fYVel = Fraction(0);
            }
            if(fYPos > Fraction(nWindowHeight - 64))
            {
                fYPos = Fraction(nWindowHeight - 64);
                fYVel = Fraction(0);
            }
            if(fXPos < Fraction(0))
            {
                fXPos = Fraction(0);
                fXVel = Fraction(0);
            }
            if(fXPos > Fraction(nWindowWidth - 64))
            {
                fXPos = Fraction(nWindowWidth - 64);
                fXVel = Fraction(0);
            }
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
        return float(fXPos);
    }
    
    float GetYPos()
    {
        return float(fYPos);
    }
    
    float GetXVel()
    {
        return float(fXVel);
    }
    
    float GetYVel()
    {
        return float(fYVel);
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
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        Clear(olc::BLACK);
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
        
        
        DrawStringDecal({ 0.0f, 0.0f }, std::to_string(p.GetXPos()) + ", " + std::to_string(p.GetYPos()) + ", " + std::to_string(p.GetXVel()) + ", " + std::to_string(p.GetYVel()), {0, 255, 0});
        return true;
    }
};

int main(int argc, char const *argv[])
{
	PortalDemo demo;
	if (demo.Construct(nWindowWidth, nWindowHeight, 1, 1, false, true))
		demo.Start();

	return 0;
}
