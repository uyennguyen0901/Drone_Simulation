#define _USE_MATH_DEFINES
#include "Drone.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include "JumpDecorator.h"
#include "SpinDecorator.h"
#include "BatteryDecorator.h"
#include "Singleton.h"


Drone::Drone(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};
  speed = obj["speed"];
  available = true;
}

Drone::~Drone() {
  // Delete dynamically allocated variables
  delete graph;
  delete nearestEntity;
  delete toRobot;
  delete toFinalDestination;
}

void Drone::GetNearestEntity(std::vector<IEntity*> scheduler) {
  float minDis = std::numeric_limits<float>::max();
  for (auto entity : scheduler) {
    if (entity->GetAvailability()) {
      float disToEntity = this->position.Distance(entity->GetPosition());
      if (disToEntity <= minDis) {
        minDis = disToEntity;
        nearestEntity = entity;
      }
    }
  }
  if (nearestEntity) {
    nearestEntity->SetAvailability(false);
    available = false;
    pickedUp = false;

    destination = nearestEntity->GetPosition();
    Vector3 finalDestination = nearestEntity->GetDestination();

    toRobot = new BeelineStrategy(position, destination);

    std::string strat = nearestEntity->GetStrategyName();
    if (strat == "astar") {
      toFinalDestination = new JumpDecorator(
        new AstarStrategy(destination, finalDestination, graph));
    } else if (strat == "dfs") {
        toFinalDestination =
          new SpinDecorator(
            new JumpDecorator(
              new DfsStrategy(destination, finalDestination, graph)));
    } else if (strat == "dijkstra") {
      toFinalDestination =
        new JumpDecorator(
          new SpinDecorator(
            new DijkstraStrategy(destination, finalDestination, graph)));
    } else {
      toFinalDestination = new BeelineStrategy(destination, finalDestination);
    }
  }
}
void Drone::Update(double dt, std::vector<IEntity*> scheduler,
std::vector<IEntity*> stations) {
  if (available)
    GetNearestEntity(scheduler);
  if (toRobot) {
    Vector3 prevPos = GetPosition();
    toRobot->Move(this, dt);
    Vector3 currentPos = GetPosition();
    float distance = prevPos.Distance(currentPos);
    SetTripDistance(GetTripDistance() + distance);
    if (toRobot->IsCompleted()) {
      delete toRobot;
      toRobot = nullptr;
      pickedUp = true;
    }
    SetTripDuration(GetTripDuration() + dt);
  } else if (toFinalDestination) {
    nearestEntity->SetTripDuration(nearestEntity->GetTripDuration() + dt);
    SetTripDuration(GetTripDuration() + dt);
    Vector3 prevPos = GetPosition();
    toFinalDestination->Move(this, dt);
    Vector3 currentPos = GetPosition();
    float distance = prevPos.Distance(currentPos);
    SetTripDistance(GetTripDistance() + distance);
    SetTripDuration(GetTripDuration() + dt);
    if (nearestEntity && pickedUp) {
      distance = (this->GetPosition()).Distance(nearestEntity->GetPosition());
      nearestEntity->SetTripDistance(
      nearestEntity->GetTripDistance() + distance);
      nearestEntity->SetPosition(position);
      nearestEntity->SetDirection(direction);
    }
    if (toFinalDestination->IsCompleted()) {
      Singleton* theInstance = Singleton::getInstance();
      // Uncomment to checking drone update percentage
      // cout << GetPercentage()<< " percent in drone"<< endl;
      nearestEntity->SetPercentage(GetPercentage());
      IncrementDeliveryVolume();
      nearestEntity->IncrementDeliveryVolume();
      theInstance->setUpData(this);
      theInstance->setUpData(nearestEntity);
      delete toFinalDestination;
      toFinalDestination = nullptr;
      nearestEntity = nullptr;
      available = true;
      pickedUp = false;
    }
  }
}

void Drone::Rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}

void Drone::Jump(double height) {
  if (goUp) {
    position.y += height;
    jumpHeight += height;
    if (jumpHeight > 5) {
      goUp = false;
    }
  } else {
    position.y -= height;
    jumpHeight -= height;
    if (jumpHeight < 0) {
      goUp = true;
    }
  }
}
