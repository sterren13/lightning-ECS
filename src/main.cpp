#include <iostream>
#include "ECS/registery.h"

// TODO add sorting of entities by component

using namespace lightning;

struct Position {
    float x, y;
};

struct Velocity {
    float x, y;
};

struct Mass {
    float mass;
};

struct Health {
    float health;
};

struct Name {
    std::string name;
};

DEFINE_TAG(tag1, 46544654165);
DEFINE_TAG(tag2, 54695121566);

ECS::registry registry;

void Print_View(){
    auto view = registry.view<Position, Name>({ tag1, EXCLUDE_TAG(tag2) }, ECS::Excludes<Health>());
    if (view->size() == 0)
        std::cout << "  No entities" << std::endl;
    else
        for (ECS::Entity_t entity : *view){
            auto& name = view->Get<Name>(entity);
            std::cout << "  " << name.name << std::endl;
        }
}

void Print_View2(){
    auto view = registry.view<Position, Name>({ tag1, EXCLUDE_TAG(tag2) }, ECS::Excludes<Health>());
    if (view->size() == 0)
        std::cout << "  No entities" << std::endl;
    else
        for (ECS::Entity_t entity : *view){
            auto& name = view->Get<Name>(entity);
            std::cout << "  " << name.name << std::endl;
        }
}

void Print_View3(){
    auto view = registry.view<Position, Name>();
    if (view->size() == 0)
        std::cout << "  No entities" << std::endl;
    else
        for (ECS::Entity_t entity : *view){
            auto& name = view->Get<Name>(entity);
            std::cout << "  " << name.name << std::endl;
        }
}

int main() {
    auto entity1 = registry.CreateEntity();
    Name name1 = {"Bob"};
    registry.Add<Name>(entity1, name1);
    registry.Add<Position>(entity1);
    registry.Add<Velocity>(entity1);
    registry.Add<Mass>(entity1);
    registry.AddTag(entity1, tag1);

    auto entity2 = registry.CreateEntity();
    Name name2 = {"Alice"};
    registry.Add<Name>(entity2, name2);
    registry.Add<Position>(entity2);
    registry.Add<Velocity>(entity2);
    registry.Add<Health>(entity2);
    registry.AddTag(entity2, tag1);

    auto entity3 = registry.CreateEntity();
    Name name3 = {"John"};
    registry.Add<Name>(entity3, name3);
    registry.Add<Position>(entity3);

    std::cout << "Before adding Health to John: \n";
    Print_View();

    registry.AddTag(entity3, tag1);

    std::cout << "After adding Health to John: \n";
    Print_View();

    registry.Add<Health>(entity3);

    std::cout << "After adding Health to John: \n";
    Print_View();

    registry.Remove<Health>(entity2);

    std::cout << "After removing Health from Alice: \n";
    Print_View();

    registry.RemoveTag(entity1, tag1);


    std::cout << "After removing tag1 from Bob: \n";
    Print_View2();

    registry.AddTag(entity2, tag2);

    std::cout << "After adding tag2 to Alice: \n";
    Print_View2();


    std::cout << "view3\n";
    Print_View3();
    return 0;
}
