//
//  Player.hpp
//  Hello PGE
//
//  Created by Kevin Puig on 9/23/20.
//  Copyright © 2020 Kevin Puig. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "LoopingEntity.hpp"

class Player : public kpg::LoopingEntity
{
private:
    float Gravity;
    float XVel, YVel;
    float XAccel;
    float XVelMax;

    bool OnCreate() override;
    bool OnUpdate() override;
    bool OnDestroy() override;
    
};

#endif /* Player_hpp */
