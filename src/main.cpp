#define OLC_PGE_APPLICATION
#include "LoopingEntity.hpp"
#include "olcPixelGameEngine.h"

#include <cstdlib>
#include <mutex>
#include <unordered_map>

const int nWindowWidth = 1920;
const int nWindowHeight = 1080;

bool start = false;
bool bJumped = false;
bool bMovingLeft = false;
bool bMovingRight = false;

std::mutex EntityIDLock;
uint32_t NewEntityID = 0;

std::unordered_map<uint32_t, std::pair<std::string, std::shared_ptr<kpg::LoopingEntity>>> Entities;

class BouncyBall : public kpg::LoopingEntity
{
private:
    float Gravity;
    float XVel, YVel;

    bool OnCreate() override
    {
        while(!EntityIDLock.try_lock());
        ID = NewEntityID++;
        EntityIDLock.unlock();
        Gravity = 1000.0f;
        XPos = float(rand() % (nWindowWidth - 32));
        YPos = float(rand() % (nWindowHeight - 32));
        YVel = float(rand() % 1000);
        XVel = float(rand() % 1000);
        Period = 1; // In milliseconds

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
};

class Player : public kpg::LoopingEntity
{
private:
    float Gravity;
    float XVel, YVel;
    float XAccel;
    float XVelMax;

    bool OnCreate() override
    {
        // Override values here. Do some other stuff too maybe
        // Velocity is pixels per second and acceleration is pixels per second^2
        while(!EntityIDLock.try_lock());
        ID = NewEntityID++;
        EntityIDLock.unlock();
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
};

class PortalDemo : public olc::PixelGameEngine
{
private:
#define ballcount 1
    std::map<std::string, std::shared_ptr<olc::Renderable>> imgs;
public:
    PortalDemo()
    {
        sAppName = "Gravity";
    }

public:
    bool OnUserCreate() override
    {
        std::string playerimage = "player.png";
        std::shared_ptr<olc::Renderable> player;
        std::string ballimage = "ball.png";
        std::shared_ptr<olc::Renderable> ball;
        imgs.insert_or_assign(playerimage, player);
        imgs.insert_or_assign(ballimage, ball);

        std::shared_ptr<kpg::LoopingEntity> p = std::make_shared<Player>();
        p.get()->Spawn();
        imgs[playerimage].get()->Load(playerimage);
        Entities.insert_or_assign(p.get()->getID(), std::pair<std::string, std::shared_ptr<kpg::LoopingEntity>>( playerimage, p ) );
        
        imgs[ballimage].get()->Load(ballimage);
        for(int i = 0; i < ballcount; i++)
        {
            std::shared_ptr<kpg::LoopingEntity> b = std::make_shared<BouncyBall>();
            b.get()->Spawn();
            Entities.insert_or_assign(p.get()->getID(), std::pair<std::string, std::shared_ptr<kpg::LoopingEntity>>( ballimage, b ) );
        }

        for(auto i = Entities.begin(); i != Entities.end(); i++)
        {
            for(auto j = Entities.begin(); j != Entities.end(); j++)
            {
                if(i != j && i->second.second.get()->getID() == j->second.second.get()->getID())
                    std::cout << "NOOOOO!!!";
            }
        }

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        Clear(olc::BLACK);

        if(GetKey(olc::E).bPressed)
            return false;

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
        
        
        for(auto i = Entities.begin(); i != Entities.end(); i++)
        {
            if(i->second.second.get()->Exists())
            {
                DrawDecal({ i->second.second.get()->GetXPos(), i->second.second.get()->GetYPos() }, imgs[i->second.first].get()->Decal());
            }
        }

        return true;
    }

    bool OnUserDestroy() override 
    {
        return true;
    }
};

int main(int argc, char const *argv[])
{
    srand(uint32_t(time(nullptr)));
	PortalDemo demo;
	if (demo.Construct(nWindowWidth, nWindowHeight, 1, 1, false, false))
		demo.Start();

	return 0;
}
