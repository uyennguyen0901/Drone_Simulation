#include "SimulationModel.h"

#include "DroneFactory.h"
#include "RobotFactory.h"
#include "HumanFactory.h"
#include "HelicopterFactory.h"
#include "ChargerFactory.h"
#include "BatteryDecorator.h"
#include <iostream>
using namespace std;
SimulationModel::SimulationModel(IController& controller)
    : controller(controller) {
  compFactory = new CompositeFactory();
  AddFactory(new DroneFactory());
  AddFactory(new RobotFactory());
  AddFactory(new HumanFactory());
  AddFactory(new HelicopterFactory());
  AddFactory(new ChargerFactory());
}

SimulationModel::~SimulationModel() {
  // Delete dynamically allocated variables
  for (int i = 0; i < entities.size(); i++) {
    delete entities[i];
  }
  for (int i = 0; i < scheduler.size(); i++) {
    delete scheduler[i];
  }
  delete graph;
  delete compFactory;
}

void SimulationModel::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  std::string name = entity["name"];
  JsonArray position = entity["position"];
  std::cout << name << ": " << position << std::endl;

  IEntity* myNewEntity = compFactory->CreateEntity(entity);
  myNewEntity->SetGraph(graph);

  // Call AddEntity to add it to the view
  if (type == "charger") {
    chargers.push_back(myNewEntity);
  } else {
    entities.push_back(myNewEntity);
  }
  controller.AddEntity(*myNewEntity);
}

/// Schedules a trip for an object in the scene
void SimulationModel::ScheduleTrip(JsonObject& details) {
  std::string name = details["name"];
  JsonArray start = details["start"];
  JsonArray end = details["end"];
  std::cout << name << ": " << start << " --> " << end << std::endl;

  for (auto entity : entities) {  // Add the entity to the scheduler
    JsonObject detailsTemp = entity->GetDetails();
    std::string nameTemp = detailsTemp["name"];
    std::string typeTemp = detailsTemp["type"];
    if (name.compare(nameTemp) == 0 && typeTemp.compare("robot") == 0 &&
        entity->GetAvailability()) {
      std::string strategyName = details["search"];
      entity->SetDestination(Vector3(end[0], end[1], end[2]));
      entity->SetStrategyName(strategyName);
      scheduler.push_back(entity);
      break;
    }
  }
  controller.SendEventToView("TripScheduled", details);
}

/// Updates the simulation
void SimulationModel::Update(double dt) {
  for (int i = 0; i < entities.size(); i++) {
    entities[i]->Update(dt, scheduler, chargers);
    controller.UpdateEntity(*entities[i]);
  }
}

void SimulationModel::AddFactory(IEntityFactory* factory) {
  compFactory->AddFactory(factory);
}
