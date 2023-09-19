#define _USE_MATH_DEFINES
#include "BatteryDecorator.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "AstarStrategy.h"
#include "DijkstraStrategy.h"
#include "Singleton.h"
#include <cmath>
#include <limits>
using namespace std;
BatteryDecorator::BatteryDecorator(Drone *drone) {
  this->drone = drone;
  percentage = 500;
  SetPercentage(percentage);
}

BatteryDecorator::~BatteryDecorator() {
  // Delete dynamically allocated variables
}

void BatteryDecorator::Update(double dt, std::vector<IEntity*> scheduler,
std::vector<IEntity*> stations) {
  if (percentage > 100) {
    drone->SetColor("#00FFFF");
  } else {
    drone->SetColor("#A10003");
  }
  if (drone->GetAvailability()) {
    needCharge = false;
    checkCharge = false;
    drone->Update(dt, scheduler, stations);
  } else {
    if (percentage >= 0) {
      if (!checkCharge) {
        GetNearestStation(stations);
        checkCharge = true;
        int len = drone->GetRobotStrategy()->GetPath().size() - 1;
        Vector3 temp = Vector3(
        drone->GetRobotStrategy()->GetPath().at(len).at(0),
        drone->GetRobotStrategy()->GetPath().at(len).at(1),
        drone->GetRobotStrategy()->GetPath().at(len).at(2));
        if ((percentage - (totalDistance(drone->GetToRobotStrategy()->GetPath())
        + totalDistance(drone->GetRobotStrategy()->GetPath())
        + temp.Distance(nearestStation->GetPosition())) * 5) < 0) {
          toRobot = new BeelineStrategy(drone->GetPosition(),
          nearestStation->GetPosition());
          needCharge = true;
        }
      }
      if (checkCharge && needCharge) {
        if (toRobot->IsCompleted()) {
          percentage += dt * 50;
          if (percentage >= 500) {
            percentage = 500;
            needCharge = false;
          }
        } else {
          toRobot->Move(this, dt);
          percentage -= dt * 5;
        }
      } else {
        if (!(drone->GetRobotStrategy() == nullptr)) {
          percentage -= dt * 5;
          drone->Update(dt, scheduler, stations);
        }
      }
    }
  }
  drone->SetPercentage(GetPercentage());
}

void BatteryDecorator::GetNearestStation(vector<IEntity*> stations) {
  float minDis = std::numeric_limits<float>::max();
  for (auto entity : stations) {
    float disToEntity = GetPosition().Distance(entity->GetPosition());
    if (disToEntity <= minDis) {
      minDis = disToEntity;
      nearestStation = entity;
    }
  }
}

float BatteryDecorator::totalDistance(std::vector<std::vector<float>> path) {
  float totalDistance = 0;
  int maxIndex = path.size() - 1;
  for (int i = 0; i < maxIndex; i++) {
    Vector3 cur = Vector3
    (path.at(i).at(0), path.at(i).at(1), path.at(i).at(2));
    Vector3 nex = Vector3
    (path.at(i+1).at(0), path.at(i+1).at(1), path.at(i+1).at(2));
    totalDistance += cur.Distance(nex);
  }
  return totalDistance;
}
