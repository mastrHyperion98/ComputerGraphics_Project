//
// Created by Steven Smith on 2020-04-05.
//

#ifndef INC_371PROCEDURALFOREST_WORLD_H
#define INC_371PROCEDURALFOREST_WORLD_H

#include "Transform.h"
#include "Entity.h"
#include <vector>
#include "glm/glm.hpp"

class World {
public:
    World();
    World(const World&);
    ~World();
    void Draw();
    void AddEntities(Entity&);
    void RemoveEntity(int index);
    Entity& GetEntity(int index){return world_entities[index];}
    void Update();
    static World& getCurrent();
    Transform getTransform(){return worldTransform;};
private:
    Transform worldTransform;
    std::vector<Entity> world_entities;
    static World current;
};


#endif //INC_371PROCEDURALFOREST_WORLD_H
