#define OLC_PGE_APPLICATION
#include "LoopingEntity.hpp"
#include "olcPixelGameEngine.h"

#include <cstdlib>
#include <mutex>
#include <unordered_map>
#include <unordered_set>

const int nWindowWidth = 1280;
const int nWindowHeight = 800;

bool start = false;
bool bJumped = false;
bool bMovingLeft = false;
bool bMovingRight = false;

std::unordered_map<uint32_t, std::pair<std::string, kpg::LoopingEntity*>> Entities;
std::unordered_set<uint32_t> KnownIDs;
uint32_t NextID = 0;
uint32_t getNextID()
{
    while(KnownIDs.count(NextID) > 0)
    {
        NextID++;
    }
    KnownIDs.insert(NextID);
    return NextID;
}

class BouncyBall : public kpg::LoopingEntity
{
private:
    float Gravity;
    float XVel, YVel;

    bool OnCreate() override
    {
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
#define ballcount 50
    std::unordered_map<std::string, olc::Renderable*> imgs;
public:
    PortalDemo()
    {
        sAppName = "Gravity";
    }

public:
    bool OnUserCreate() override
    {
        std::string playerimage = "player.png";
        olc::Renderable * player = new olc::Renderable();
        player->Load(playerimage);
        std::string ballimage = "ball.png";
        olc::Renderable * ball = new olc::Renderable();
        ball->Load(ballimage);
        
        imgs[playerimage] = player;
        imgs[ballimage] = ball;

        kpg::LoopingEntity * p = new Player();
        p->Spawn();
        std::pair<std::string, kpg::LoopingEntity*> newplayer(playerimage, p);
        Entities[getNextID()] = newplayer;
        for(int i = 0; i < ballcount; i++)
        {
            kpg::LoopingEntity * b = new BouncyBall();
            b->Spawn();
            std::pair<std::string, kpg::LoopingEntity*> newball(ballimage, b);
            Entities[getNextID()] = newball;
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
        
        for(const auto & [key, val] : Entities)
        {
            if(val.second->Exists())
            {
                std::cout << key << " " << val.first << std::endl;
                DrawDecal({ val.second->GetXPos(), val.second->GetYPos() }, imgs[val.first]->Decal());
                FillRectDecal({ val.second->GetXPos(), val.second->GetYPos() }, { 32.0f, 8.0f }, olc::BLACK);
                DrawStringDecal({ val.second->GetXPos(), val.second->GetYPos() }, std::to_string(key));
            }
        }
        
        std::cout << "=================\n";

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
	if (demo.Construct(nWindowWidth, nWindowHeight, 1, 1, false, true))
		demo.Start();

	return 0;
}
