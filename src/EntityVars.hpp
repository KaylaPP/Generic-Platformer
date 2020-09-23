#ifndef EntityVars_hpp
#define EntityVars_hpp

#include "LoopingEntity.hpp"

#include <unordered_map>
#include <unordered_set>

const int nWindowWidth = 1280;
const int nWindowHeight = 800;

extern bool start;
extern bool bJumped;
extern bool bMovingLeft;
extern bool bMovingRight;

extern std::unordered_map<uint32_t, std::pair<std::string, kpg::LoopingEntity*>> Entities;
extern std::unordered_set<uint32_t> KnownIDs;

#endif /* EntityVars_h */
